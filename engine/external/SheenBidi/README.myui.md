# SheenBidi (vendored for myui, M11a)

Upstream: https://github.com/Tehreer/SheenBidi v3.0.0
License: Apache License 2.0 (see LICENSE)
Source of this copy: ~/opensource/awtk/3rd/SheenBidi-3.0.0 (Headers/ + Source/
only; Tests/Tools/build scripts not vendored).

Used for: Unicode Bidirectional Algorithm (UBA) paragraph direction +
visual reordering in src/myr/my_text_layout.c. Built as a unity TU
(Source/SheenBidi.c with SB_CONFIG_UNITY) with relaxed warnings; myui's
own strict warning bar does not apply to this third-party code.

NOTE: SheenBidi 3.0.0 has NO Arabic shaping (joining -> presentation
forms) — myui implements that itself in src/myr/my_arabic_shape.[ch]
(data generated from the local UCD, see tools/gen_arabic_shape_data.py).
