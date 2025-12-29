Bombardier, the GNU Bombing Utility

Bombardier (from the Debian upstream repository) uses ISO-8859-2 (Latin-2) encoding for Hungarian scientist names in the Hall of Fame, which breaks on macOS. MacOS not only expects UTF-8, but has deprecated Latin-2 completely to the point where macOS utilities can even fail to perform replacement operations on Latin-2 characters. The game also assumes 1 byte = 1 character for column alignment, and multi-byte UTF-8 characters destroy the fixed-width table formatting. As a result, there is corruption of the Hall of Fame (HoF) that can't be fixed without losing the diacritics or overhaul of the column alignment scheme.

Additionally, there is hard-coding of pathways to linux folders and what is probably an orphaned HoF generation pathway.

This formula includes five patches:

1. Replace Hungarian names with ASCII (hof.c)

Converts Latin-2 encoded names (Szilárd Leó → Szilard Leo)
Uses binary string matching to find the exact bytes
Preserves 20-character width for proper column alignment
Sadly, this loses the diacritics but it's the least disruptive patch

2. Fix the score file path (hof.c)

Changes /var/games/bombardier/bdscore → #{var}/games/gnu-bombardier/bdscore
Uses Homebrew's managed var/ directory instead of system location
No sudo required, works in user space

3. Skip installing the Latin-2 bdscore file (Makefile)

Comments out the install bdscore line and related chmod/chown commands
Let the game auto-generate a clean ASCII version on first run
The patched defhof() function creates the correct format
This uses the existing function; it just disables a redundant path

4. Install as gnu-bombardier

Renames binary to avoid conflict with existing bombardier package (HTTP benchmark tool)
Creates var/games/gnu-bombardier/ directory for high scores

5. Add zap support

Allows complete uninstall including saved scores
brew uninstall --zap gnu-bombardier removes everything
