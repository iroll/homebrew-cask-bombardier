#!/usr/bin/perl

$i=-1;
print "struct struc_texts texts[] = \n{\n";
if ($line=<STDIN>) {$i=$i+1;}
if ($line=~/^\d*-/)
{
    ($minfloor, $maxfloor, $text) = $line =~ /(\d*)-(\d*)\#(.*)/;
}
else
{
    ($minfloor, $text) = $line =~ /(\d*)\#(.*)/;
    $maxfloor=$minfloor;
}
$text=~s/\"/\\\"/g;
while ($line=<STDIN>)
{
    $i=$i+1;
    print "    {$minfloor, $maxfloor, \"$text\"},\n";
    if ($line=~/^\d*-/)
    {
	($minfloor, $maxfloor, $text) = $line =~ /(\d*)-(\d*)\#(.*)/;
    }
    else
    {
	($minfloor, $text) = $line =~ /(\d*)\#(.*)/;
	$maxfloor=$minfloor;
    }
    $text=~s/\"/\\\"/g;
} 
if ($i!=-1) {print "    {$minfloor, $maxfloor, \"$text\"}\n";}
print "};\n";
print "#define NUM_OF_TEXTS ";
print $i+1;
print "\n";
