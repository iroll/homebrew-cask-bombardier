class GnuBombardier < Formula
  desc "Bombardier, The GNU Bombing utility"
  homepage "https://salsa.debian.org/games-team/bombardier"
  url "https://salsa.debian.org/games-team/bombardier.git",
      tag: "debian/0.8.3+nmu4",
      revision: "fdfc6ff8f7edfc4d5e76f97a729a99f45ad07ceb"
  version "0.8.3.4"
  license "GPL-3.0-or-later"
  head "https://salsa.debian.org/games-team/bombardier.git", branch: "master"

  depends_on "ncurses"

  def install
    # Replace Latin-2 encoded Hungarian names with ASCII for macOS compatibility
    inreplace "hof.c" do |s|
      s.gsub!("Szil\xE1rd Le\xF3".b, "Szilard Leo")
      s.gsub!("Neumann J\xE1nos".b, "Neumann Janos")
      s.gsub!("G\xE1bor D\xE9nes".b, "Gabor Denes")
      s.gsub!("Bolyai J\xE1nos".b, "Bolyai Janos")
      s.gsub!("E\xF6tv\xF6s Lor\xE1nd".b, "Eotvos Lorand")
      s.gsub!("Horthy Mikl\xF3s".b, "Horthy Miklos")
      s.gsub!("K\xE1d\xE1r J\xE1nos".b, "Kadar Janos")
      s.gsub!("R\xE1kosi M\xE1ty\xE1s".b, "Rakosi Matyas")
    end

    # Change hardcoded path to use Homebrew's var directory
    inreplace "hof.c", '"/var/games/bombardier/bdscore"',
              "\"#{var}/games/gnu-bombardier/bdscore\""

    # Don't install the Latin-2 encoded bdscore - let the game generate it
    inreplace "Makefile", /^\s*install bdscore.*$/, "# bdscore will be auto-generated"
    inreplace "Makefile", /^\s*chgrp games.*bdscore.*$/, ""
    inreplace "Makefile", /^\s*chown root.*bdscore.*$/, ""
    inreplace "Makefile", /^\s*chmod.*bdscore.*$/, ""

    # Build and install
    system "make"
    bin.install "bombardier" => "gnu-bombardier"
    man6.install "bombardier.6" => "gnu-bombardier.6"

    # Create score directory
    (var/"games/gnu-bombardier").mkpath
  end

  def caveats
    <<~EOS
      High scores are stored in:
        #{var}/games/gnu-bombardier/bdscore

      To completely remove the game including high scores:
        brew uninstall --zap gnu-bombardier
    EOS
  end

  test do
    assert_predicate bin/"gnu-bombardier", :exist?
  end

  def zap
    rm_rf var/"games/gnu-bombardier"
  end
end