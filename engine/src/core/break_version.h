#pragma once

/* ---- Product version / build identity ----
 *
 * Bump rules (pre-1.0 product; documented decision):
 *  - MAJOR: reserved for the 1.0 product-line transition; stays 0 until then.
 *  - MINOR: bumps per delivered roadmap stage/phase that adds user-visible
 *    capability (Stage 5 Phase A starts the triple at 0.1.0).
 *  - PATCH: bumps for fixes/polish within a phase that change shipped bytes.
 * The update compatibility policy (signed-manifest min-version, Stage 5
 * subproject 1) compares against this triple; see
 * docs/design/security_threat_model.md. */
#define BREAK_VERSION_MAJOR 0  /* product triple starts 0.1.0; bump rules documented */
#define BREAK_VERSION_MINOR 1
#define BREAK_VERSION_PATCH 0

/* Returns "MAJOR.MINOR.PATCH[+buildid]" — static storage, never NULL.
 * The "+buildid" suffix is present iff BREAK_BUILD_ID was defined (as a
 * non-empty string literal) at compile time; CMake injects the short git
 * hash and falls back to "unknown". Repeated calls return the same pointer. */
const char *break_version_string(void);
