## [1.0.0] - 2026-01-11

### Added
- Full encapsulation with opaque `ColdJail` struct
- Order-independent argument parser
- MIT license (SPDX headers in all source files)

### Changed
- Refactored codebase to pseudo-OO style in C
- Improved mount security flags (`MS_NOSUID`, `MS_NOEXEC`)
- All user-facing messages remain in English

### Removed
- Direct struct access — now fully encapsulated


## [0.2.0] - 2026-01-06

### Changed
- All user-facing messages (stdout/stderr) are now in English.
- Shell is now launched with `-i` to ensure interactive mode.

### Chores
- Adopted Semantic Versioning (MAJOR.MINOR.PATCH) for releases.
- Initial version `v0.1` is now formally `v0.1.0`.
