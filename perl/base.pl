#!/usr/bin/perl -w

use strict;

use File::Basename qw/basename/;

use File::Spec;

use CGI qw(:all);

chomp(my @mylist=<STDIN>);

@mylist=reverse @mylist;

@mylist=sort @mylist;

my $var1=pop(@mylist);

push(@mylist, $var1);

my $var2=shift(@mylist);

unshift(@mylist, $var2);

my $cnt=scalar(@mylist);

my $scalarcnt=@mylist;

my @numlist=(1..10);

my @nulllist=();

my $mystr="My String";

my $mylen=length($mystr);

#@ARGV -> argument list

#$ARGV -> arg in used

open MYINPUT, "<mytxt.in" or die "Sys Error: $!";

open MYOUTPUT, ">>mytxt.out" || die "Sys Error: $!";

printf MYOUTPUT "@mylist\n";

select MYOUTPUT; #set as default filehandle

$|=1; #do not buffer the data in MYOUTPUT

print "APPEND STRINGS TO THIS FILE\n";

select STDOUT; #set back

open STDERR, "error.log" or "$!, restore the original one.";

my %myhash=("k1"=>"v1", "k2"=>"v2");

$myhash{"k3"}=undef;

my %inverse_hash=reverse %myhash; #(value,key,value,key,...)

my @hashlist=%myhash;

my @mykeys=keys %myhash;

my @myvalues=values %myhash;

(my $key, my $value)=each %myhash;

exists $myhash{"k3"} or print "k3 doesnt exist";

delete $myhash{"k2"};

while(<MYINPUT>){s/\[.*\]/[\u\L$mystr\E Replaced]/g;print;}

#\d=[0-9]    \w=[A-Za-z0-9_]    \s=[\f\t\n\r ] 5 types

#\D=[^\d]    \W=[^\w]           \S=[^\s]

#m/pattern/ixsm

#   s->match any character 

#   x->ignore literal space 

#   i->case insensitive

#   m->match multiline text

#Anchors: line /^\s$/, word /\b($word)\b/, \B not word

#$str=~m/match/  $` before, $& match, $' after

my @fields=split /\s+/, $mystr;

$mystr=join "\t", @fields;

my($first, $second)=($mystr=~/(\w+)\s+(\w+)/);#parenthesis

my @mystrlist=($mystr=~/(\S+)/g); #/g is needed

#perl -p -i.bak -w -e 's/(^#!.*\n)/$1#${mystr}\n'/ myfile

#$^I=".out"; #only used for <>

#m/(?:pattern)/ #?: non-capturing parentheses

print "unless 0\n" unless 0; 

print "$cnt \t" and $cnt+=1 until $cnt>@numlist; 

#loop control "last", "next", "redo", label the loop & line

#file tests, -r,-w,-x,-e,-s,-z,-M,-A,-C,-f,-d,-l,stat,lstat

my($dev, $ino, $mode, $nlink, $uid, $gid, $rdev, $size,

$atime, $mtime, $ctime, $blksize, $blockes)=stat("mytxt.in");

my $mydate=localtime; #Wed Oct 30 12:58:59 2013 

my @mydatelist=localtime;#sec,min,hour,day,mon,year,wday,yday,isdst

#year since 1900, wday 0~6, mon 0~11, yday 0~364

my $mygdate=gmtime; #return Greenwich Mean Time

$_="mytxt.out"; print "\n_\n" if (-s)>1000 and -f _; #_ reuse $_ 

chdir "/home/fbgu/src/cc" or die "Sys Error: $!";

my @myfiles=glob ".* *" or warn "$!";

unlink <*.o>;

rename "a.cc", "aa.cc";

link "aa.cc", "aah.cc" or warn "can not do hard link: $!";

symlink "aa.cc", "aal.cc" or warn "symbol link fail: $!";

mkdir "aaadir", 0755 or warn "$!";

chmod 0744, "aaadir";

#uid=10185(fbgu) gid=24(cc_rdr_mxranc) groups=24(cc_rdr_mxranc)

#my $user=getpwnam "fbgu";           #get 10185

#my $group=getgrnam "cc_rdr_mxranc"; #get 24

#chown $user, $group, @myfiles;

opendir MYDIR, "/home/fbgu/src/shell" or die "Sys Error: $!";

foreach (readdir MYDIR){print $_."\n";}

closedir MYIDR;

my $mymtime=time-24*60*60*100; #unit second, 100days ago

utime $atime, $mymtime, @myfiles; #set atime and mtime  

my $myidx=index($mystr, "i", 0); #begin position 0

my $mylastidx=rindex($mystr, "i");

my $mysubstr=substr($mystr, 3, 6); #begin position3, len 5

sub mysort{$inverse_hash{$b} cmp $inverse_hash{$a}} #num to use <=>

print sort mysort keys %inverse_hash; #subroutin no & notation

system 'for i in *.cc; do cat $i>myappend.txt; done'; #shell script

#Perl enviroment hash "%ENV",$ENV{'PATH'}="...";

#backquotes capture the output my $now=`date`;

my $whos=`ls -l`;    #one text contain all lines

my @wholist=`ls -l`; #one list, stored by seperated lines

open MYFIND, "find ~/src/cc/ -name '*.cc'|" or die "$!"; #| exe cmd

print `basename $_`  while(<MYFIND>);

#open MYMAIL, "|mail fbgu" or die "$!"; print MYMAIL "Hi~";

defined(my $mypid=fork) or die "can't fork,$!";

unless($mypid){#system "date";

my $fullname=File::Spec->catfile("/home/fbgu/src/perl", "notes_perl.txt");

my @myoddnums=grep{$_%2}@numlist; #grep {m/pattern/} <FILE>

my @myoddstrs=map{sprintf"%5.2f\$",$_}@myoddnums; #modified list of copy with map

print "@myoddnums and @myoddstrs", $fullname."\n";

};kill 9, $mypid;waitpid($mypid,0);

#eval{} capture errors, $@ store the num of errors 

#my($first, $last) = (sort @names)[0, -1];

#@items[2, 3] = ($new_address, $new_phone_phone);

my @two_values = @myhash{ qw/k1 k2/ };

#my @players = qw/ barney fred dino /;

#my @bowling_scores = (195, 205, 30);

#@score{ @players } = @bowling_scores;


#Perl new learning knowledge:

perl ¨Cne ¡®print if /match/¡¯ file.plx  #same as grep ¡®match¡¯ file.plx

-array functions

delete $array[1];  #not delete, just set to undef

splice @array, 1, 1; #delete this item

 

$index=grep /match/, @array; #get matched index

@subarray=grep /match/, @array; #get matched sub-array

 

#delete 3 items begin index 2 and replace with 2 new items(n1 and n2)

splice(@array, 2, 3, ¡°n1¡±, ¡°n2¡±);

 

ATTEMPT: {  #loop block
  print "Are you a great person? ";
  chomp($answer = <STDIN>);
  unless ($answer eq "yes"){redo ATTEMPT;} #last, next for ¡®while¡¯ ¡¯foreach¡¯ loop
}
