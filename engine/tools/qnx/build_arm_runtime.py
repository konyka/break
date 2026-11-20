#!/usr/bin/env python3
"""Generate an SSH-enabled AArch64 test IFS from the qemu-virt BSP."""

import argparse
from pathlib import Path


SSH_FILES = r"""
/sbin/rtc=${QNX_TARGET}/${PROCESSOR}/sbin/rtc
/usr/sbin/sshd=${QNX_TARGET}/${PROCESSOR}/usr/sbin/sshd
/usr/libexec/sshd-auth=${QNX_TARGET}/${PROCESSOR}/usr/libexec/sshd-auth
/usr/libexec/sshd-session=${QNX_TARGET}/${PROCESSOR}/usr/libexec/sshd-session
/usr/bin/ssh-keygen=${QNX_TARGET}/${PROCESSOR}/usr/bin/ssh-keygen
/usr/bin/scp=${QNX_TARGET}/${PROCESSOR}/usr/bin/scp
/usr/libexec/sftp-server=${QNX_TARGET}/${PROCESSOR}/usr/libexec/sftp-server
/proc/boot/sshd_config = {
Port 22
ListenAddress 0.0.0.0
HostKey /var/ssh_host_ed25519_key
PermitRootLogin yes
PasswordAuthentication yes
KbdInteractiveAuthentication no
UsePAM no
AllowUsers root
PidFile /var/run/sshd.pid
Subsystem sftp /usr/libexec/sftp-server
}
"""


def customize_buildfile(source: str, ram_mib: int = 256) -> str:
    if ram_mib < 1:
        raise ValueError("RAM filesystem size must be positive")
    for marker in (
            "[image=0x40200000]",
            "startup-qemu-virt -u reg",
            "devf-ram -i 9,0 -s0,16m",
            "customize_startup.sh = {\n#!/bin/ksh\n"):
        if source.count(marker) != 1:
            raise ValueError(f"expected exactly one BSP marker: {marker!r}")
    if "/proc/boot/sshd_config = {" in source:
        raise ValueError("buildfile already contains the test SSH configuration")

    result = source.replace(
        "devf-ram -i 9,0 -s0,16m",
        f"devf-ram -i 9,0 -s0,{ram_mib}m", 1)
    marker = "customize_startup.sh = {\n#!/bin/ksh\n"
    start = result.index(marker) + len(marker)
    end = result.index("\n}\n", start)
    startup = """

rtc -b 0x9010000 primecell
if [ ! -f /var/ssh_host_ed25519_key ]; then
    ssh-keygen -q -t ed25519 -N '' -f /var/ssh_host_ed25519_key
fi
/usr/sbin/sshd -f /proc/boot/sshd_config"""
    return result[:end] + startup + result[end:] + SSH_FILES


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("buildfile", type=Path, help="qemu-virt buildfile")
    parser.add_argument("output", type=Path, help="generated buildfile")
    parser.add_argument("--ram-mib", type=int, default=256)
    args = parser.parse_args()
    try:
        result = customize_buildfile(
            args.buildfile.read_text(encoding="utf-8"), args.ram_mib)
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(result, encoding="utf-8")
    except (OSError, ValueError) as error:
        parser.error(str(error))
    print(f"generated {args.output} with {args.ram_mib} MiB RAM filesystem")


if __name__ == "__main__":
    main()
