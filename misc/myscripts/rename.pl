#!/usr/bin/perl -w

my $len=@ARGV;

$len eq 2 or die "help: ./rename.pl [from] [to]\n";

my $from=$ARGV[0];
my $to=$ARGV[1];

$from ne $to or die "2 arguments are totally identical.\n";

#@files=glob "*";
@files=`find`;
my $oldfile;
my $newfile;

sub rename_file{
  $oldfile = $_[0];
  $newfile = $oldfile;
  printf "$oldfile";
  $newfile =~ s/$from/$to/g;
  printf "----->$newfile\n";
  rename $oldfile, $newfile;
}

foreach $file(@files){
 chomp $file;
 #if(-d $file)
 if($file=~/$from/){
  rename_file($file);
 }
}
