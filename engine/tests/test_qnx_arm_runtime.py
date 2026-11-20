#!/usr/bin/env python3
import importlib.util
import json
import os
import subprocess
import sys
import tarfile
import tempfile
from pathlib import Path
from types import SimpleNamespace
import unittest
from unittest import mock

sys.dont_write_bytecode = True


MODULE_PATH = Path(__file__).parents[1] / "tools/qnx/build_arm_runtime.py"
SPEC = importlib.util.spec_from_file_location("build_arm_runtime", MODULE_PATH)
MODULE = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(MODULE)

STAGE_PATH = Path(__file__).parents[1] / "tools/qnx/stage_screen_runtime.py"
STAGE_SPEC = importlib.util.spec_from_file_location("stage_screen_runtime", STAGE_PATH)
STAGE = importlib.util.module_from_spec(STAGE_SPEC)
STAGE_SPEC.loader.exec_module(STAGE)

ANGLE_STAGE_PATH = Path(__file__).parents[1] / "tools/qnx/stage_angle_runtime.py"
ANGLE_STAGE_SPEC = importlib.util.spec_from_file_location("stage_angle_runtime", ANGLE_STAGE_PATH)
ANGLE_STAGE = importlib.util.module_from_spec(ANGLE_STAGE_SPEC)
ANGLE_STAGE_SPEC.loader.exec_module(ANGLE_STAGE)


class AngleRuntimeStageTests(unittest.TestCase):
    def test_versioned_target_paths_are_written_to_all_configs(self):
        with tempfile.TemporaryDirectory() as temporary:
            output = Path(temporary) / "runtime"
            ANGLE_STAGE.stage_angle_configs(output, "/var/angle-run-17")
            manifest = json.loads((output / "angle/vk_swiftshader_icd.json").read_text())
            self.assertEqual(manifest["ICD"]["library_path"],
                             "/var/angle-run-17/swiftshader/libvk_swiftshader.so")
            graphics = (output / "graphics.conf").read_text()
            self.assertIn("egl-dlls = /var/angle-run-17/angle/libEGL.so", graphics)
            self.assertIn("glesv2-dlls = /var/angle-run-17/angle/libGLESv2.so", graphics)
            self.assertIn("vk-icds = /var/angle-run-17/angle/vk_swiftshader_icd.json", graphics)
            self.assertEqual((output / "vk_swiftshader_icd.json").read_text(),
                             (output / "angle/vk_swiftshader_icd.json").read_text())


DEPLOY_PATH = Path(__file__).parents[1] / "tools/qnx/deploy_arm_suite.sh"
RUNNER_PATH = Path(__file__).parents[1] / "tools/qnx/run_target_suite.sh"


class ArmRuntimeBuildfileTests(unittest.TestCase):
    def setUp(self):
        self.source = (
            "[image=0x40200000]\n"
            "[virtual=aarch64le,raw -compress] boot = {\n"
            "    startup-qemu-virt -u reg\n"
            "}\n"
            ".storage-server.sh = {\n"
            "devf-ram -i 9,0 -s0,16m\n"
            "}\n"
            "customize_startup.sh = {\n"
            "#!/bin/ksh\n"
            "echo ready\n"
            "}\n"
        )

    def test_ram_and_ssh_are_configured_without_host_paths(self):
        result = MODULE.customize_buildfile(self.source, ram_mib=256)
        self.assertIn("devf-ram -i 9,0 -s0,256m", result)
        self.assertNotIn("devf-ram -i 9,0 -s0,16m", result)
        self.assertIn("startup-qemu-virt -u reg", result)
        self.assertIn("rtc -b 0x9010000 primecell", result)
        self.assertIn("/sbin/rtc=${QNX_TARGET}/${PROCESSOR}/sbin/rtc", result)
        self.assertIn("/usr/sbin/sshd -f /proc/boot/sshd_config", result)
        self.assertIn("${QNX_TARGET}/${PROCESSOR}/usr/libexec/sshd-session", result)
        self.assertIn("ListenAddress 0.0.0.0", result)
        self.assertIn("PidFile /var/run/sshd.pid", result)
        self.assertNotIn("/home/", result)
        self.assertEqual(result.count("/proc/boot/sshd_config = {"), 1)

    def test_ram_size_is_checked(self):
        with self.assertRaises(ValueError):
            MODULE.customize_buildfile(self.source, ram_mib=0)

    def test_incomplete_bsp_input_is_rejected(self):
        with self.assertRaises(ValueError):
            MODULE.customize_buildfile("[image=0x40200000]\n")

    def test_missing_customization_hook_is_rejected(self):
        source = self.source.replace("customize_startup.sh", "other.sh")
        with self.assertRaises(ValueError):
            MODULE.customize_buildfile(source)


def write_elf(path, machine=183, elf_class=2):
    path.parent.mkdir(parents=True, exist_ok=True)
    data = bytearray(64)
    data[:4] = b"\x7fELF"
    data[4] = elf_class
    data[5] = 1
    data[18:20] = machine.to_bytes(2, "little")
    path.write_bytes(data)


class VulkanRuntimeStageTests(unittest.TestCase):
    def setUp(self):
        temporary = tempfile.TemporaryDirectory()
        self.addCleanup(temporary.cleanup)
        base = Path(temporary.name)
        self.root = base / "qnx/aarch64le"
        self.output = base / "output"
        self.inputs = base / "inputs"
        self.paths = {}
        for name in (
            "libvk_swiftshader.so", "libvulkan.so.1",
            "libgraphics_conf_redirect.so", "libshaderc_shared.so.1",
        ):
            self.paths[name] = self.inputs / name
            write_elf(self.paths[name])
        self.candidates = {}
        for name in ("libc++.so.2", "libm.so.3", "libc.so.6", "libgcc_s.so.1"):
            path = self.root / "usr/lib" / name
            if name == "libc++.so.2":
                write_elf(path.with_name("libc++.so.2.0"))
                path.symlink_to("libc++.so.2.0")
            else:
                write_elf(path)
            self.candidates[name] = path
        self.manifest = self.inputs / "swiftshader_icd.json"
        self.manifest.write_text(json.dumps({
            "file_format_version": "1.0.0",
            "ICD": {"library_path": "/old/libvk_swiftshader.so", "api_version": "1.3.0"},
        }), encoding="utf-8")
        self.graphics = self.inputs / "graphics.conf"
        self.graphics.write_text(
            "begin khronos\n  begin egl display 1\n"
            "    vk-icds = /old/swiftshader_icd.json\n"
            "  end egl display\nend khronos\n", encoding="utf-8")
        self.args = SimpleNamespace(
            vulkan_target_root="/var/bt", output=self.output, arch="aarch64le",
            vulkan_icd=self.paths["libvk_swiftshader.so"],
            vulkan_loader=self.paths["libvulkan.so.1"],
            vulkan_redirect=self.paths["libgraphics_conf_redirect.so"],
            shaderc=self.paths["libshaderc_shared.so.1"],
            vulkan_icd_manifest=self.manifest,
            vulkan_graphics_config=self.graphics,
        )
        self.dependencies = {
            "libvk_swiftshader.so": ["libc++.so.2", "libm.so.3", "libc.so.6", "libgcc_s.so.1"],
            "libshaderc_shared.so.1": ["libc++.so.2", "libm.so.3", "libc.so.6", "libgcc_s.so.1"],
            "libvulkan.so.1": ["libm.so.3", "libc.so.6", "libgcc_s.so.1"],
            "libgraphics_conf_redirect.so": ["libc.so.6", "libgcc_s.so.1"],
            "libc++.so.2": ["libm.so.3", "libc.so.6", "libgcc_s.so.1"],
        }

    def fake_readelf(self, command, text):
        dependencies = self.dependencies.get(Path(command[-1]).name, [])
        return "\n".join(f"Shared library: [{name}]" for name in dependencies)

    def stage(self, output=None):
        if output is not None:
            self.args.output = output
        with mock.patch.object(STAGE.subprocess, "check_output", self.fake_readelf):
            return STAGE.stage_vulkan_runtime(
                self.args, self.root, Path("readelf"), self.candidates)

    def test_closure_and_target_configuration_are_staged(self):
        self.assertEqual(self.stage(), 8)
        expected = [
            "swiftshader/libvk_swiftshader.so",
            "swiftshader/libshaderc_shared.so.1",
            "swiftshader/libgraphics_conf_redirect.so",
            "usr/lib/libvulkan.so.1",
            "swiftshader/lib/libc++.so.2",
            "swiftshader/lib/libm.so.3",
            "swiftshader/lib/libc.so.6",
            "swiftshader/lib/libgcc_s.so.1",
        ]
        for relative in expected:
            self.assertTrue((self.output / relative).is_file(), relative)
        manifest = json.loads((self.output / "swiftshader/swiftshader_icd.json").read_text())
        self.assertEqual(manifest["ICD"]["library_path"],
                         "/var/bt/swiftshader/libvk_swiftshader.so")
        self.assertEqual(manifest["ICD"]["api_version"], "1.3.0")
        graphics = (self.output / "swiftshader/graphics.conf").read_text()
        self.assertIn("vk-icds = /var/bt/swiftshader/swiftshader_icd.json", graphics)
        self.assertNotIn("/old/", graphics)
        self.assertNotIn(str(self.inputs), graphics)

    def add_sanitizer_fixture(self, include_stdcpp=True):
        for name in ("libasan.so.8.0.0", "libubsan.so.1.0.0"):
            path = self.root / "lib" / name
            write_elf(path)
            self.dependencies[name] = ["libstdc++.so.6", "libm.so.3", "libc.so.6", "libgcc_s.so.1"]
        stdcpp = self.root / "usr/lib/libstdc++.so.6"
        write_elf(stdcpp)
        if include_stdcpp:
            self.candidates["libstdc++.so.6"] = stdcpp
        self.dependencies["libstdc++.so.6"] = ["libm.so.3", "libc.so.6", "libgcc_s.so.1"]

    def test_sanitizer_runtime_closure_and_soname_links(self):
        self.add_sanitizer_fixture()
        with mock.patch.object(STAGE.subprocess, "check_output", self.fake_readelf):
            count = STAGE.stage_sanitizer_runtime(
                self.output, "aarch64le", self.root, Path("readelf"), self.candidates,
                use_asan=True, use_ubsan=True)
        self.assertEqual(count, 6)
        for name in (
            "libasan.so.8.0.0", "libubsan.so.1.0.0", "libstdc++.so.6",
            "libm.so.3", "libc.so.6", "libgcc_s.so.1",
        ):
            self.assertTrue((self.output / name).is_file(), name)
        self.assertEqual((self.output / "libasan.so.8").readlink(),
                         Path("libasan.so.8.0.0"))
        self.assertEqual((self.output / "libubsan.so.1").readlink(),
                         Path("libubsan.so.1.0.0"))

    def test_sanitizer_cleanup_is_staged_with_architecture_check(self):
        self.add_sanitizer_fixture()
        cleanup = self.inputs / "libqnx_sanitizer_cleanup.so"
        write_elf(cleanup)
        with mock.patch.object(STAGE.subprocess, "check_output", self.fake_readelf):
            count = STAGE.stage_sanitizer_runtime(
                self.output, "aarch64le", self.root, Path("readelf"), self.candidates,
                use_asan=True, use_ubsan=True, cleanup=cleanup)
        self.assertEqual(count, 7)
        self.assertTrue((self.output / "libqnx_sanitizer_cleanup.so").is_file())

    def test_sanitizer_runtime_missing_stdcpp_is_rejected(self):
        self.add_sanitizer_fixture(include_stdcpp=False)
        with mock.patch.object(STAGE.subprocess, "check_output", self.fake_readelf):
            with self.assertRaisesRegex(RuntimeError, "libstdc\\+\\+"):
                STAGE.stage_sanitizer_runtime(
                    self.output, "aarch64le", self.root, Path("readelf"), self.candidates,
                    use_asan=True, use_ubsan=False)

    def test_missing_dependency_is_rejected(self):
        del self.candidates["libgcc_s.so.1"]
        with self.assertRaisesRegex(RuntimeError, "libgcc_s.so.1"):
            self.stage(self.output.parent / "missing")

    def test_wrong_architecture_is_rejected(self):
        write_elf(self.paths["libvk_swiftshader.so"], machine=62)
        with self.assertRaisesRegex(RuntimeError, "aarch64le"):
            self.stage(self.output.parent / "wrong-arch")


class TargetSuiteVulkanTests(unittest.TestCase):
    def setUp(self):
        temporary = tempfile.TemporaryDirectory()
        self.addCleanup(temporary.cleanup)
        self.root = Path(temporary.name) / "target"
        runtime = self.root / "swiftshader"
        for relative in (
            "libvulkan.so.1", "swiftshader/libvk_swiftshader.so",
            "swiftshader/libshaderc_shared.so.1",
            "swiftshader/lib/libc++.so.2",
            "swiftshader/libgraphics_conf_redirect.so",
            "swiftshader/graphics.conf", "swiftshader/swiftshader_icd.json",
        ):
            path = self.root / relative
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_bytes(b"runtime")
        (runtime / "lib").mkdir(parents=True, exist_ok=True)
        (self.root / "cmds.txt").write_text("./test_dummy\n", encoding="utf-8")
        self.fake_bin = self.root / "fake-bin"
        self.fake_bin.mkdir()
        self.probe = self.root / "probe.log"
        fake_sh = self.fake_bin / "sh"
        fake_sh.write_text(
            "#!/bin/bash\n"
            "printf 'command=%s\\n' \"$2\" > \"$RUNNER_PROBE_LOG\"\n"
            "printf 'ld_library_path=%s\\n' \"$LD_LIBRARY_PATH\" >> \"$RUNNER_PROBE_LOG\"\n"
            "printf 'graphics_conf=%s\\n' \"$SWIFTSHADER_GRAPHICS_CONF\" >> \"$RUNNER_PROBE_LOG\"\n"
            "printf 'icd=%s\\n' \"$VK_ICD_FILENAMES\" >> \"$RUNNER_PROBE_LOG\"\n"
            "if [ -n \"${RUNNER_FAKE_OUTPUT:-}\" ]; then\n"
            "  printf '%s\\n' \"$RUNNER_FAKE_OUTPUT\"\n"
            "fi\n"
            "exit \"${RUNNER_FAKE_RC:-0}\"\n", encoding="utf-8")
        fake_sh.chmod(0o755)

    def run_suite(self, vulkan="1", tls="0", asan_lock=None, cleanup="0", normal_root=None,
                  fake_output=None, fake_rc=0):
        env = os.environ.copy()
        env.pop("LD_PRELOAD", None)
        env.pop("LD_LIBRARY_PATH", None)
        env.pop("BREAK_QNX_ASAN_LOCK", None)
        env.update({
            "PATH": str(self.fake_bin) + os.pathsep + env["PATH"],
            "RUNNER_PROBE_LOG": str(self.probe),
            "RUNNER_FAKE_RC": str(fake_rc),
            "BREAK_QNX_TARGET_ROOT": str(self.root),
            "BREAK_QNX_VULKAN_RUNTIME": vulkan,
            "BREAK_QNX_TLS_INTERPOSE": tls,
            "BREAK_QNX_SANITIZER_CLEANUP": cleanup,
            "BREAK_QNX_ON_AD": "0",
        })
        if fake_output is not None:
            env["RUNNER_FAKE_OUTPUT"] = fake_output
        if asan_lock is not None:
            env["BREAK_QNX_ASAN_LOCK"] = str(asan_lock)
        if normal_root is not None:
            env["BREAK_QNX_NORMAL_ROOT"] = str(normal_root)
        return subprocess.run(
            ["/bin/sh", str(RUNNER_PATH), "cmds.txt"], cwd=self.root,
            env=env, capture_output=True, text=True)

    def test_asan_lock_rejects_held_directory(self):
        lock = self.root / "asan.lock"
        lock.mkdir()
        result = self.run_suite(vulkan="0", asan_lock=lock)
        self.assertEqual(result.returncode, 3, result.stdout + result.stderr)
        self.assertIn("another ASan run", result.stderr)
        self.assertFalse(self.probe.exists())

    def test_asan_lock_is_removed_after_success(self):
        lock = self.root / "asan.lock"
        result = self.run_suite(vulkan="0", asan_lock=lock)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertFalse(lock.exists())
        self.assertTrue(self.probe.exists())

    def test_vulkan_runtime_is_opt_in(self):
        result = self.run_suite()
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        probe = self.probe.read_text()
        self.assertIn(
            f"LD_PRELOAD={self.root}/swiftshader/lib/libc++.so.2:"
            f"{self.root}/swiftshader/libgraphics_conf_redirect.so ./test_dummy",
            probe)
        self.assertIn(
            f"ld_library_path={self.root}:{self.root}/swiftshader:{self.root}/swiftshader/lib",
            probe)
        self.assertIn(f"graphics_conf={self.root}/swiftshader/graphics.conf", probe)
        self.assertIn(f"icd={self.root}/swiftshader/swiftshader_icd.json", probe)
        self.assertIn("not a physical GPU", result.stdout)

    def test_default_suite_does_not_inject_vulkan(self):
        result = self.run_suite(vulkan="0")
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        probe = self.probe.read_text()
        self.assertIn("command=./test_dummy", probe)
        self.assertNotIn("LD_PRELOAD=", probe)
        self.assertIn(f"ld_library_path={self.root}\n", probe)
        self.assertIn("graphics_conf=\n", probe)
        self.assertIn("icd=\n", probe)

    def test_tls_only_does_not_add_vulkan_redirect(self):
        for name in ("libasan.so.8", "libubsan.so.1", "libqnx_tls_general_interpose.so"):
            (self.root / name).write_bytes(b"tls")
        result = self.run_suite(vulkan="0", tls="1")
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        probe = self.probe.read_text()
        self.assertIn(f"LD_PRELOAD={self.root}/libasan.so.8", probe)
        self.assertNotIn("libgraphics_conf_redirect.so", probe)

    def test_libcxx_precedes_sanitizers_when_combined(self):
        for name in ("libasan.so.8", "libubsan.so.1", "libqnx_tls_general_interpose.so"):
            (self.root / name).write_bytes(b"tls")
        result = self.run_suite(tls="1")
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        expected = (
            f"{self.root}/swiftshader/lib/libc++.so.2:"
            f"{self.root}/libasan.so.8:{self.root}/libubsan.so.1:"
            f"{self.root}/libqnx_tls_general_interpose.so:"
            f"{self.root}/swiftshader/libgraphics_conf_redirect.so"
        )
        self.assertIn(f"LD_PRELOAD={expected} ./test_dummy", self.probe.read_text())

    def add_cleanup_files(self):
        for name in (
            "libstdc++.so.6", "libasan.so.8", "libubsan.so.1",
            "libqnx_sanitizer_cleanup.so",
        ):
            (self.root / name).write_bytes(b"cleanup")

    def test_cleanup_preload_order(self):
        self.add_cleanup_files()
        result = self.run_suite(cleanup="1")
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        expected = (
            f"{self.root}/swiftshader/lib/libc++.so.2:"
            f"{self.root}/libstdc++.so.6:{self.root}/libasan.so.8:"
            f"{self.root}/libubsan.so.1:{self.root}/libqnx_sanitizer_cleanup.so:"
            f"{self.root}/swiftshader/libgraphics_conf_redirect.so"
        )
        self.assertIn(f"LD_PRELOAD={expected} ./test_dummy", self.probe.read_text())

    def test_cleanup_missing_helper_fails_before_tests(self):
        self.add_cleanup_files()
        (self.root / "libqnx_sanitizer_cleanup.so").unlink()
        result = self.run_suite(cleanup="1")
        self.assertEqual(result.returncode, 2)
        self.assertIn("libqnx_sanitizer_cleanup.so", result.stderr)
        self.assertFalse(self.probe.exists())

    def test_cleanup_rejects_tls_interpose(self):
        self.add_cleanup_files()
        (self.root / "libqnx_tls_general_interpose.so").write_bytes(b"tls")
        result = self.run_suite(cleanup="1", tls="1")
        self.assertEqual(result.returncode, 2)
        self.assertIn("BREAK_QNX_SANITIZER_CLEANUP", result.stderr)
        self.assertFalse(self.probe.exists())

    def test_cleanup_requires_vulkan_runtime(self):
        self.add_cleanup_files()
        result = self.run_suite(cleanup="1", vulkan="0")
        self.assertEqual(result.returncode, 2)
        self.assertIn("BREAK_QNX_VULKAN_RUNTIME=1", result.stderr)
        self.assertFalse(self.probe.exists())

    def cleanup_preload(self):
        return (
            f"{self.root}/swiftshader/lib/libc++.so.2:"
            f"{self.root}/libstdc++.so.6:{self.root}/libasan.so.8:"
            f"{self.root}/libubsan.so.1:{self.root}/libqnx_sanitizer_cleanup.so:"
            f"{self.root}/swiftshader/libgraphics_conf_redirect.so"
        )

    def add_normal_executable(self, name):
        normal = self.root / "normal"
        normal.mkdir(exist_ok=True)
        executable = normal / name
        executable.write_bytes(b"normal")
        executable.chmod(0o755)
        return normal

    def test_cleanup_death_helper_does_not_preload_sanitizer(self):
        self.add_cleanup_files()
        (self.root / "cmds.txt").write_text("./test_break_crash\n", encoding="utf-8")
        normal = self.add_normal_executable("test_break_crash")
        result = self.run_suite(cleanup="1", normal_root=normal)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertIn(
            f"command=env LD_PRELOAD={self.cleanup_preload()} "
            f"BREAK_QNX_DEATH_CHILD={normal}/test_break_crash ./test_break_crash",
            self.probe.read_text())
        self.assertIn("no child ASan coverage", result.stdout)

    def test_cleanup_child_overrides_survive_preload_composition(self):
        self.add_cleanup_files()
        normal = self.add_normal_executable("test_break_crash")
        self.add_normal_executable("test_mypal_screen_ipc")
        cases = (
            ("test_break_crash", "BREAK_QNX_DEATH_CHILD"),
            ("test_mypal_screen_ipc", "BREAK_MYPAL_IPC_CHILD_EXECUTABLE"),
        )
        for executable, variable in cases:
            for wrapped in (False, True):
                with self.subTest(executable=executable, wrapped=wrapped):
                    command = f"./{executable} --tail-arg value"
                    expected_prefix = (
                        f"command=env LD_PRELOAD={self.cleanup_preload()} "
                        f"{variable}={normal}/{executable} "
                    )
                    if wrapped:
                        command = (
                            "on -ad env ASAN_OPTIONS=detect_leaks=1 "
                            f"UBSAN_OPTIONS=print_stacktrace=1 {command}"
                        )
                        expected_prefix = (
                            f"command=on -ad env LD_PRELOAD={self.cleanup_preload()} "
                            f"{variable}={normal}/{executable} "
                            "ASAN_OPTIONS=detect_leaks=1 UBSAN_OPTIONS=print_stacktrace=1 "
                        )
                    (self.root / "cmds.txt").write_text(command + "\n", encoding="utf-8")
                    result = self.run_suite(cleanup="1", normal_root=normal)
                    self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
                    self.assertIn(expected_prefix + f"./{executable} --tail-arg value",
                                  self.probe.read_text())
                    self.assertIn("no child ASan coverage", result.stdout)

    def test_tls_exclusion_preserves_override_and_tail_arguments(self):
        for name in ("libasan.so.8", "libubsan.so.1", "libqnx_tls_general_interpose.so"):
            (self.root / name).write_bytes(b"tls")
        normal = self.add_normal_executable("test_break_crash")
        expected_preload = (
            f"{self.root}/swiftshader/lib/libc++.so.2:"
            f"{self.root}/swiftshader/libgraphics_conf_redirect.so"
        )
        for wrapped in (False, True):
            with self.subTest(wrapped=wrapped):
                command = "./test_break_crash --tail-arg value"
                expected_prefix = (
                    f"command=env LD_PRELOAD={expected_preload} "
                    f"BREAK_QNX_DEATH_CHILD={normal}/test_break_crash "
                )
                if wrapped:
                    command = (
                        "on -ad env ASAN_OPTIONS=detect_leaks=1 "
                        f"UBSAN_OPTIONS=print_stacktrace=1 {command}"
                    )
                    expected_prefix = (
                        f"command=on -ad env LD_PRELOAD={expected_preload} "
                        f"BREAK_QNX_DEATH_CHILD={normal}/test_break_crash "
                        "ASAN_OPTIONS=detect_leaks=1 UBSAN_OPTIONS=print_stacktrace=1 "
                    )
                (self.root / "cmds.txt").write_text(command + "\n", encoding="utf-8")
                result = self.run_suite(tls="1", normal_root=normal)
                self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
                probe = self.probe.read_text()
                self.assertIn(expected_prefix + "./test_break_crash --tail-arg value", probe)
                self.assertNotIn("libqnx_tls_general_interpose.so", probe)
                self.assertNotIn("libasan.so.8", probe)
                self.assertIn("without TLS interpose", result.stdout)
                self.assertIn("no child ASan coverage", result.stdout)

    def test_sanitizer_leak_expect_fail_requires_lsan_signature(self):
        cases = {
            "crash": "Segmentation fault",
            "loader": "error while loading shared libraries: libasan.so.8",
            "wrong-size": (
                "ERROR: LeakSanitizer: detected memory leaks\n"
                "SUMMARY: AddressSanitizer: 45 byte(s) leaked in 1 allocation(s)."
            ),
        }
        for name, output in cases.items():
            with self.subTest(name=name):
                (self.root / "cmds.txt").write_text(
                    "EXPECT_FAIL ./test_qnx_sanitizer_leak\n"
                    "EXPECT_FAIL ./test_other_expected_failure\n", encoding="utf-8")
                result = self.run_suite(vulkan="0", fake_output=output, fake_rc=1)
                self.assertEqual(result.returncode, 1, result.stdout + result.stderr)
                self.assertIn("PASS ./test_other_expected_failure", result.stdout)
                self.assertIn("1 passed, 1 failed", result.stdout)
                self.assertIn("123 byte(s) leaked", result.stderr)

    def test_sanitizer_leak_expect_fail_accepts_exact_lsan_signature(self):
        output = (
            "==123==ERROR: LeakSanitizer: detected memory leaks\n"
            "Direct leak of 123 byte(s) in 1 object(s) allocated from:\n"
            "SUMMARY: AddressSanitizer: 123 byte(s) leaked in 1 allocation(s)."
        )
        for command in (
            "./test_qnx_sanitizer_leak",
            "on -ad env ./test_qnx_sanitizer_leak",
        ):
            with self.subTest(command=command):
                (self.root / "cmds.txt").write_text(
                    f"EXPECT_FAIL {command}\n", encoding="utf-8")
                result = self.run_suite(vulkan="0", fake_output=output, fake_rc=1)
                self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
                self.assertIn("1 passed, 0 failed", result.stdout)

    def test_missing_runtime_file_fails_before_running_tests(self):
        (self.root / "swiftshader/libshaderc_shared.so.1").unlink()
        result = self.run_suite()
        self.assertEqual(result.returncode, 2)
        self.assertIn("libshaderc_shared.so.1", result.stderr)
        self.assertFalse(self.probe.exists())

    def test_missing_libcxx_fails_before_running_tests(self):
        (self.root / "swiftshader/lib/libc++.so.2").unlink()
        result = self.run_suite()
        self.assertEqual(result.returncode, 2)
        self.assertIn("libc++.so.2", result.stderr)
        self.assertFalse(self.probe.exists())


class SpawnEnvironmentTests(unittest.TestCase):
    def test_normal_child_envp_drops_only_ld_preload(self):
        source = r'''
#define _POSIX_C_SOURCE 200809L
#define TEST_QNX_SPAWN_HELPERS_ONLY
#include "test_qnx_spawn.h"

static const char *env_value(char *const envp[], const char *name) {
    size_t length = strlen(name);
    size_t index;
    for (index = 0; envp[index] != NULL; ++index) {
        if (strncmp(envp[index], name, length) == 0 && envp[index][length] == '=') {
            return envp[index] + length + 1;
        }
    }
    return NULL;
}

int main(void) {
    char **child_envp;
    char **same_envp;
    if (setenv("LD_PRELOAD", "/sanitizer/libasan.so.8", 1) != 0 ||
        setenv("LD_LIBRARY_PATH", "/normal:/normal/lib:/crypto", 1) != 0 ||
        setenv("BREAK_TEST_KEEP", "preserved", 1) != 0 ||
        setenv("BREAK_QNX_DEATH_CHILD", "/normal/test_child", 1) != 0) {
        return 1;
    }
    child_envp = test_qnx_spawn_child_envp(getenv("BREAK_QNX_DEATH_CHILD"));
    if (child_envp == NULL || child_envp == environ) return 2;
    if (env_value(child_envp, "LD_PRELOAD") != NULL) return 3;
    if (strcmp(env_value(child_envp, "LD_LIBRARY_PATH"),
               "/normal:/normal/lib:/crypto") != 0) return 4;
    if (strcmp(env_value(child_envp, "BREAK_TEST_KEEP"), "preserved") != 0) return 5;
    if (strcmp(getenv("LD_PRELOAD"), "/sanitizer/libasan.so.8") != 0) return 6;
    test_qnx_spawn_child_envp_destroy(child_envp);
    if (strcmp(getenv("LD_PRELOAD"), "/sanitizer/libasan.so.8") != 0) return 7;
    same_envp = test_qnx_spawn_child_envp(NULL);
    if (same_envp != environ) return 8;
    if (strcmp(env_value(same_envp, "LD_PRELOAD"),
               "/sanitizer/libasan.so.8") != 0) return 9;
    return 0;
}
'''
        with tempfile.TemporaryDirectory() as temporary:
            base = Path(temporary)
            probe_source = base / "spawn_env_probe.c"
            probe = base / "spawn_env_probe"
            probe_source.write_text(source, encoding="utf-8")
            compiled = subprocess.run(
                [os.environ.get("CC", "cc"), "-std=c11", "-Wall", "-Wextra", "-Werror",
                 "-I", str(Path(__file__).parent), str(probe_source), "-o", str(probe)],
                capture_output=True, text=True)
            self.assertEqual(compiled.returncode, 0, compiled.stdout + compiled.stderr)
            result = subprocess.run([str(probe)], capture_output=True, text=True)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)

        for name in ("test_qnx_spawn.h", "test_break_crash.c", "test_mypal_screen_ipc.c"):
            with self.subTest(source=name):
                contents = Path(__file__).with_name(name).read_text(encoding="utf-8")
                self.assertIn("test_qnx_spawn_child_envp(", contents)
                self.assertIn("arguments, child_envp)", contents)


class DeployScriptTests(unittest.TestCase):
    def test_partial_vulkan_inputs_fail_before_target_access(self):
        with tempfile.TemporaryDirectory() as temporary:
            base = Path(temporary)
            build = base / "build"
            build.mkdir()
            (build / "CMakeCache.txt").write_text("", encoding="utf-8")
            executable = build / "test_platform_compat"
            executable.write_bytes(b"test")
            executable.chmod(0o755)
            icd = base / "libvk_swiftshader.so"
            icd.write_bytes(b"icd")
            fake_bin = base / "bin"
            fake_bin.mkdir()
            file_tool = fake_bin / "file"
            file_tool.write_text("#!/bin/sh\necho 'ELF 64-bit ARM aarch64'\n", encoding="utf-8")
            file_tool.chmod(0o755)
            env = os.environ.copy()
            env.update({
                "PATH": str(fake_bin) + os.pathsep + env["PATH"],
                "QNX_HOST": str(base / "host"),
                "QNX_TARGET": str(base / "target"),
                "QNX_SDP_DIR": "",
                "QNX_ARM_DEPLOY_WORKDIR": str(base / "work"),
                "QNX_ARM_VULKAN_ICD": str(icd),
            })
            for name in (
                "QNX_ARM_VULKAN_LOADER", "QNX_ARM_VULKAN_REDIRECT", "QNX_ARM_SHADERC",
                "QNX_ARM_VULKAN_ICD_MANIFEST", "QNX_ARM_VULKAN_GRAPHICS_CONF",
            ):
                env.pop(name, None)
            result = subprocess.run(
                ["/bin/bash", str(DEPLOY_PATH), str(build), "deploy"],
                env=env, capture_output=True, text=True)
            self.assertEqual(result.returncode, 2, result.stdout + result.stderr)
            self.assertIn("must be provided together", result.stderr)
            self.assertFalse((base / "work").exists())

    def test_deploy_passes_sanitizer_flags_from_build_cache(self):
        with tempfile.TemporaryDirectory() as temporary:
            base = Path(temporary)
            build = base / "build"
            build.mkdir()
            (build / "CMakeCache.txt").write_text(
                "ENGINE_USE_ASAN:BOOL=ON\nENGINE_USE_UBSAN:BOOL=ON\n", encoding="utf-8")
            executable = build / "test_platform_compat"
            executable.write_bytes(b"test")
            executable.chmod(0o755)
            graphics = build / "test_vulkan"
            graphics.write_bytes(b"test")
            graphics.chmod(0o755)
            fake_bin = base / "bin"
            fake_bin.mkdir()
            (fake_bin / "file").write_text(
                "#!/bin/sh\necho 'ELF 64-bit ARM aarch64'\n", encoding="utf-8")
            (fake_bin / "file").chmod(0o755)
            probe = base / "stage-args.log"
            (fake_bin / "python").write_text(
                "#!/bin/bash\n"
                "printf '%s\\n' \"$*\" >> \"$DEPLOY_PROBE\"\n"
                "case \"$1\" in\n"
                "  *gen_target_cmds.py) printf './test_platform_compat\\n' > \"${@: -1}\" ;;\n"
                "  *stage_screen_runtime.py)\n"
                "    output=\n"
                "    while [ \"$#\" -gt 0 ]; do\n"
                "      if [ \"$1\" = --output ]; then output=$2; shift 2; else shift; fi\n"
                "    done\n"
                "    mkdir -p \"$output\" ;;\n"
                "  -c) exec /usr/bin/python3 \"$@\" ;;\n"
                "esac\n"
                "exit 0\n", encoding="utf-8")
            (fake_bin / "python").chmod(0o755)
            (fake_bin / "ssh").write_text(
                "#!/bin/sh\necho 'QNX localhost 8.0.0 aarch64le'\nexit 0\n",
                encoding="utf-8")
            (fake_bin / "ssh").chmod(0o755)
            (fake_bin / "scp").write_text("#!/bin/sh\nexit 0\n", encoding="utf-8")
            (fake_bin / "scp").chmod(0o755)
            env = os.environ.copy()
            env.update({
                "PATH": str(fake_bin) + os.pathsep + env["PATH"],
                "PYTHON": str(fake_bin / "python"),
                "DEPLOY_PROBE": str(probe),
                "QNX_HOST": str(base / "host"),
                "QNX_TARGET": str(base / "target"),
                "QNX_SDP_DIR": "",
                "QNX_ARM_DEPLOY_WORKDIR": str(base / "work"),
                "QNX_ARM_SSH_PORT": "2301",
            })
            result = subprocess.run(
                ["/bin/bash", str(DEPLOY_PATH), str(build), "deploy"],
                env=env, capture_output=True, text=True, timeout=30)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            self.assertIn("--asan --ubsan", probe.read_text())

    def test_deploy_excludes_python_bytecode(self):
        with tempfile.TemporaryDirectory() as temporary:
            base = Path(temporary)
            source = base / "source"
            deploy_dir = source / "engine/tools/qnx"
            deploy_dir.mkdir(parents=True)
            deploy = deploy_dir / "deploy_arm_suite.sh"
            deploy.write_bytes(DEPLOY_PATH.read_bytes())
            (source / "engine/tests/data").mkdir(parents=True)
            (source / "engine/tests/data/input.txt").write_text("input\n", encoding="utf-8")
            for relative in (
                "engine/tools/qnx/__pycache__/cache.pyc",
                "engine/tests/data/__pycache__/nested.pyc",
            ):
                cached = source / relative
                cached.parent.mkdir(parents=True)
                cached.write_bytes(b"cache")
            build = base / "build"
            build.mkdir()
            (build / "CMakeCache.txt").write_text("", encoding="utf-8")
            for name in ("test_platform_compat", "test_vulkan"):
                executable = build / name
                executable.write_bytes(b"test")
                executable.chmod(0o755)
            fake_bin = base / "bin"
            fake_bin.mkdir()
            for name, script in {
                "file": "#!/bin/sh\necho 'ELF 64-bit ARM aarch64'\n",
                "ssh": "#!/bin/sh\necho 'QNX localhost 8.0.0 aarch64le'\n",
                "scp": "#!/bin/sh\nexit 0\n",
                "python": (
                    "#!/bin/bash\n"
                    "case \"$1\" in\n"
                    "  *gen_target_cmds.py) printf './test_platform_compat\\n' > \"${@: -1}\" ;;\n"
                    "  *stage_screen_runtime.py)\n"
                    "    while [ \"$#\" -gt 0 ]; do\n"
                    "      if [ \"$1\" = --output ]; then output=$2; shift 2; else shift; fi\n"
                    "    done\n"
                    "    mkdir -p \"$output\" ;;\n"
                    "  *) exec /usr/bin/python3 \"$@\" ;;\n"
                    "esac\n"
                ),
            }.items():
                tool = fake_bin / name
                tool.write_text(script, encoding="utf-8")
                tool.chmod(0o755)
            env = os.environ.copy()
            env.update({
                "PATH": str(fake_bin) + os.pathsep + env["PATH"],
                "PYTHON": str(fake_bin / "python"),
                "QNX_HOST": str(base / "host"),
                "QNX_TARGET": str(base / "target"),
                "QNX_SDP_DIR": "",
                "QNX_ARM_DEPLOY_WORKDIR": str(base / "work"),
            })
            result = subprocess.run(
                ["/bin/bash", str(deploy), str(build), "deploy"],
                env=env, capture_output=True, text=True, timeout=30)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            with tarfile.open(base / "work/engine.tar.gz", "r:gz") as archive:
                names = archive.getnames()
            self.assertTrue(any(name.endswith("tests/data/input.txt") for name in names))
            self.assertFalse(any(
                "__pycache__" in Path(name).parts or name.endswith(".pyc")
                for name in names), names)

    def test_tar_and_loopback_deploy_only_selected_artifacts(self):
        with tempfile.TemporaryDirectory() as temporary:
            base = Path(temporary)
            build = base / "build"
            build.mkdir()
            (build / "CMakeCache.txt").write_text(
                "ENGINE_TEST_SOURCE_ROOT:PATH=/var/bt/engine\n", encoding="utf-8")
            for name in (
                "test_platform_compat", "test_alpha", "test_helper", "test_vulkan",
                "not_in_cmds",
            ):
                executable = build / name
                executable.write_bytes(("exe-" + name).encode())
                executable.chmod(0o755)
            (build / "CMakeFiles").mkdir()
            (build / "CMakeFiles/junk.o").write_bytes(b"junk")
            (build / "Makefile").write_text("build\n", encoding="utf-8")
            (build / "libunneeded.so").write_bytes(b"unneeded")
            commands = base / "commands.txt"
            commands.write_text(
                "./test_platform_compat\n./test_alpha\nEXPECT_FAIL ./test_helper --flag\n",
                encoding="utf-8")

            fake_bin = base / "bin"
            fake_bin.mkdir()

            def write_tool(name, source):
                path = fake_bin / name
                path.write_text(source, encoding="utf-8")
                path.chmod(0o755)

            write_tool("file", "#!/bin/sh\necho 'ELF 64-bit ARM aarch64'\n")
            write_tool("scp", "#!/bin/sh\nexit 0\n")
            write_tool("ssh", (
                "#!/bin/bash\n"
                "case \"$*\" in\n"
                "  *'uname -a'*) echo 'QNX localhost 8.0.0 aarch64le'; exit 0 ;;\n"
                "esac\n"
                "cat >/dev/null\n"
                "exit 0\n"))
            write_tool("python", (
                "#!/bin/bash\n"
                "case \"$1\" in\n"
                "  *gen_target_cmds.py)\n"
                "    cp \"$FAKE_COMMANDS\" \"${@: -1}\"\n"
                "    ;;\n"
                "  *stage_screen_runtime.py)\n"
                "    output=\n"
                "    while [ \"$#\" -gt 0 ]; do\n"
                "      if [ \"$1\" = --output ]; then output=$2; shift 2; else shift; fi\n"
                "    done\n"
                "    mkdir -p \"$output\"\n"
                "    ;;\n"
                "  *) exec /usr/bin/python3 \"$@\" ;;\n"
                "esac\n"))
            write_tool("mkqnx6fsimg", "#!/bin/bash\n: > \"${@: -1}\"\n")

            host = base / "host"
            (host / "usr/bin").mkdir(parents=True)
            (host / "usr/bin/mkqnx6fsimg").symlink_to(fake_bin / "mkqnx6fsimg")
            target = base / "target"
            for relative in (
                "sbin/devb-loopback", "lib/libcam.so.2", "lib/libsecpol.so.1",
                "lib/libslog2.so.1", "lib/dll/io-blk.so", "lib/dll/cam-disk.so",
                "lib/dll/fs-qnx6.so",
            ):
                path = target / "aarch64le" / relative
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_bytes(b"driver")

            env = os.environ.copy()
            env.update({
                "PATH": str(fake_bin) + os.pathsep + env["PATH"],
                "PYTHON": str(fake_bin / "python"),
                "FAKE_COMMANDS": str(commands),
                "QNX_HOST": str(host),
                "QNX_TARGET": str(target),
                "QNX_SDP_DIR": "",
            })
            for name in (
                "QNX_ARM_VULKAN_ICD", "QNX_ARM_VULKAN_LOADER", "QNX_ARM_VULKAN_REDIRECT",
                "QNX_ARM_SHADERC", "QNX_ARM_VULKAN_ICD_MANIFEST",
                "QNX_ARM_VULKAN_GRAPHICS_CONF",
            ):
                env.pop(name, None)

            expected = {"test_platform_compat", "test_alpha", "test_helper", "test_vulkan"}
            for storage in ("tar", "loopback"):
                with self.subTest(storage=storage):
                    work = base / ("work-" + storage)
                    env["QNX_ARM_STORAGE"] = storage
                    env["QNX_ARM_DEPLOY_WORKDIR"] = str(work)
                    result = subprocess.run(
                        ["/bin/bash", str(DEPLOY_PATH), str(build), "deploy"],
                        env=env, capture_output=True, text=True, timeout=60)
                    self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
                    self.assertIn("staging 4 test/helper executables", result.stdout)
                    if storage == "tar":
                        with tarfile.open(work / "tests.tar.gz", "r:gz") as archive:
                            names = set(archive.getnames())
                        self.assertEqual(names, expected)
                        self.assertNotIn("not_in_cmds", names)
                        self.assertNotIn("libunneeded.so", names)
                        self.assertTrue(all("CMakeFiles" not in Path(name).parts for name in names))
                        with tarfile.open(work / "engine.tar.gz", "r:gz") as archive:
                            self.assertTrue(all(
                                "CMakeFiles" not in Path(name).parts
                                for name in archive.getnames()))
                    else:
                        image = work / "loopback-root"
                        for name in expected:
                            self.assertTrue((image / name).is_file(), name)
                        self.assertEqual((image / "test_vulkan").read_bytes(), b"exe-test_vulkan")
                        self.assertFalse((image / "not_in_cmds").exists())
                        self.assertFalse((image / "libunneeded.so").exists())
                        self.assertFalse(any(
                            path.name == "CMakeFiles" for path in image.rglob("*")))

    def test_no_ignored_runtime_path_is_hardcoded(self):
        source = DEPLOY_PATH.read_text(encoding="utf-8")
        self.assertNotIn("/home/", source)
        self.assertNotIn("build-validation/qnx-unsupported/swiftshader", source)
        for name in (
            "QNX_ARM_VULKAN_ICD", "QNX_ARM_VULKAN_LOADER", "QNX_ARM_VULKAN_REDIRECT",
            "QNX_ARM_SHADERC", "QNX_ARM_VULKAN_ICD_MANIFEST",
            "QNX_ARM_VULKAN_GRAPHICS_CONF",
        ):
            self.assertIn(name, source)


if __name__ == "__main__":
    unittest.main()
