################## my_perl_track_EX01
#! /usr/bin/perl -w
## Copyright (C) 2013 by Feng GU Truly

#EX1_1
  print "Hello World!\n";

#EX1_2
  @lines=`perldoc -u -f atan2`;
  foreach(@lines){
    s/\w<([^>]+)/\U$1/g;
    print;
  } 

################## my_perl_track_EX02
#! /usr/bin/perl -w
## Copyright (C) 2013 by Feng GU Truly

#EX2_1
  print 2*3.141592654*12.5."\n";
#EX2_2
  $radius=<STDIN>;
  chomp $radius;
#EX2_3
  if($radius lt 0){
    $radius=0;
    print "Radius is set to 0 when it gets negative value.\n";  
  }
  print 2*3.141592654*$radius."\n";

#EX2_4
  chomp($Length=<STDIN>);
  chomp($Width=<STDIN>);
  print "Area is ".$Length*$Width.".\n";

#EX2_5
  $Str=<STDIN>; 
  chomp($Num=<STDIN>); 
  print $Str x $Num;

################## my_perl_track_EX03
#! /usr/bin/perl -w
## Copyright (C) 2013 by Feng GU Truly

#EX3_1
  chomp(@Rd=<STDIN>);
  @Rd=reverse @Rd;
  foreach(@Rd){
    $_ .= " ";
  }
  print "@Rd\n";

#EX3_2
  @Names=qw[fred betty barney dino Wilma pebbles bamm-bamm];
  chomp($Idx=<STDIN>);
  print "Name is $Names[$Idx-1]\n";

#EX3_3
  @Names=sort @Names;
  print "@Names\n";
  foreach(@Names){
    print $_."\n";
  } 

  print sort <STDIN>;

################## my_perl_track_EX04
#! /usr/bin/perl -w
## Copyright (C) 2013 by Feng GU Truly

#EX4_1
  my @fred = qw{1 3 5 7 9};
  my $fred_total = &total(@fred);
  print "The total of \@fred is $fred_total.\n";
  print "Enter some number on seperate lines:\n";
  my $user_total = &total(<STDIN>);
  print "The total of some numbers is $user_total.\n";

  sub total{
    my $SUM=0;
    foreach(@_){
      $SUM+=$_;
    }
    $SUM;
  }

#EX4_2
  print "The sum of 1..1000 is ".(total(1..1000)).".\n";

#EX4_3
  my @fred = &above_average(1..10);
  print "\@fred is @fred\n";
  print "(Should be 6 7 8 9 10)\n";
  my @barney = &above_average(100, 1..10);
  print "\@barney is @barney\n";
  print "(Should be just 100)\n";

  sub above_average{
    my $SUM = total(@_);
    my $average = $SUM/@_;
    my @above = (); #not to use {}
    foreach(@_){
      if($_>$average){
        push @above, $_;
      }
    }
    @above;
  }

################## my_perl_track_EX05
#! /usr/bin/perl -w

  while(<STDIN>){
    $STR=<STDIN>;
    chomp($STR);
    chomp($_);
    $DebugLine="*********|";
    $c = $_/10;
    $L = length $STR;
    if ( $L > $_ ){
      if ( $L %10 == 0 ){
        $c = $L/10;
      }else{
        $d = $L-$_;
        if(($d%10)==0){
          $c += ($d/10);
        }else{
          $c += (($d-($L%10))/10 + 1);
        }
      }
    }
    $align=$c*10;
    print "$align\n";
    if(($align)%10>0){
      $align += 10;
      $align -= $align%10; 
    }
    print "length is ", $L, " align is ", $align, "\n";
    print $DebugLine x (($_+9)/10),"\n";
    printf "%${align}s\n", $STR;
    print $DebugLine x (($_+9)/10),"\n";
  }

#! /usr/bin/perl -w

  @Lines=();
  print "-->\$ARGV=$ARGV\n";
  print "-->\@ARGV=@ARGV\n";
  #shift @ARGV;
  while(<>){
      #print ">>>\$ARGV=$ARGV\n";
      #print ">>>\@ARGV=@ARGV\n";
      push @Lines, $_;
  }
  @Lines = reverse @Lines;
  print @Lines;
  print "-->$ARGV\n"

################## my_perl_track_EX06
#! /usr/bin/perl -w
## Copyright (C) 2013 by Feng GU Truly

#EX6_1
  my %first_name = ("Feng"=>"GU", "Chunhua"=>"GU");
  chomp($first_name=<STDIN>);
  #chomp($first_name{$first_name}=<STDIN>);
  print "$first_name is a member of $first_name{$first_name} family.\n"; 
  
#EX6_2
  while($name=<STDIN>){
    chomp($name);
    if(exists $names{$name}){
      $names{$name} += 1;
    }else{
      $names{$name} = 1;
    }
  }  
  foreach $cn(keys %names){
    print "$cn appears $names{$cn} time(s).\n";
  }

    #my(@words, %count, $word);     # (optionally) declare our variables
    chomp(@words = <STDIN>);
    foreach $word (@words) {
      $count{$word} += 1;          # or $count{$word} = $count{$word} + 1;
    }
    foreach $word (keys %count) {  # or sort keys %count
      print "$word was seen $count{$word} times.\n";
    }

################## my_perl_track_EX07
#! /usr/bin/perl -w

  while(<>){
    #if(/[Ff]red/){    #EX7_1_2
    #if(/(\.)+/){      #EX7_3
    #if(/[A-Z][a-z]+/){      #EX7_4
    if(/(wilma.*fred|fred.*wilma)+/){      #EX7_4
      print "$_";
    }
  }

################## my_perl_track_EX08
#! /usr/bin/perl -w

#EX8_1
  $match_string="beforematchafter";
  if($match_string =~ /match/){
    print "$`<$&>$'\n";
  }

#EX8_2_3_4_5
  while(<>){
    #if(/(\b\w*a\b)/){
    #if(/(\b\w*a\b)(.{5})/){ #EX4
    #chomp;
    if(/.*(\s+\n)$/){   #EX5
      chomp;
      print $_."\$\n";
      #printf "----> <%s><%s>\n", $1, $2;
    }else{
      #print "----> NO MATCH \@$_";;
    }
  }  

################## my_perl_track_EX09
#! /usr/bin/perl -w

if(0){

#EX9_1
  my $what = 'fred|barney';
  while(my $line=<>){
    if($line =~ /($what){3}/){
      print $line;
    }
  }

#EX9_2
#Command line:
#/usr/bin/perl -p -w -i.out -e 's/fred/\u\LLarry/ig/' test_file
  $^I='.out';
  while(<>){
    s/fred/\u\LLarry/ig;
    print;
  }

#EX9_3
  $^I='.out';
  while(<>){
    if(/(.*?)fred(.*\n)$/i){
    #    print "\$1=".$1."\n\$2=".$2."\n\$_=".$_."\n";
    }
    #s/fred(.*?)Wilma/\u\Lwilma\E$1\u\Lfred\E/ig;
    #s/Wilma(.*?)fred/\u\Lfred\E$1\u\Lwilma\E/ig;
    chomp;
    s/fred/\n/ig;
    s/wilma/\u\Lfred/ig;
    s/\n/\u\Lwilma/ig;
    print $_."\n";
 }

}

#EX9_4_5
#Command line:
#/usr/bin/perl -p -i.bak -w -e 's/(^#!)(.*\n)/$1$2## Copyright (C) 20XX by Yours Truly\n'/ test_file  
  my %do_files;
  foreach(@ARGV){
    $do_files{$_}=1;
  }
  while(<>){
    if(/^## Copyright/){
        delete $do_files{$ARGV};
    }
  }
  @ARGV = sort keys %do_files;
  $^I='.out';
    #open TEST_FILE, $filename
    #  or die "Can't open the target file.\n";
    #while(<TEST_FILE>){
  while(<>){
    if(/^#!/){
      $_ .= "## Copyright (C) 2013 by Feng GU Truly\n";
    }
    print;
  }

################## my_perl_track_EX10
#! /usr/bin/perl -w
## Copyright (C) 2013 by Feng GU Truly

  $secret = int( 1 + rand 100);
  print "\$secret is $secret\n";
  while(1){
    print "Please enter a guess from 1 to 100: ";
    chomp(my $guess = <STDIN>);
    if ($guess =~ /quit|exit|^\s*$/i) {
      print "Sorry you gave up. The number was $secret.\n";
      last;
    } elsif ($guess < $secret) {
      print "Too small. Try again!\n";
    } elsif ($guess == $secret) {
      print "That was it!\n";
      last;
    } else {
      print "Too large. Try again!\n";
    }
  }

################## my_perl_track_EX11
#! /usr/bin/perl -w
## Copyright (C) 2013 by Feng GU Truly

#EX11_1
  my @filenames=@ARGV;
  foreach (@filenames) {
    print "-r" if -r;
    print "--" if !-r;
    print "w" if -w;
    print "-" if !-w;
    print "x $_" if -x;
    print "- $_" if !-x;
    print " Exist\n" if -e;
    print " Don't Exist\n" if !-e;
  }

#EX11_2
  $file_name=shift @filenames;;
  $days_exist=-M $file_name;
  foreach(@filenames){
    if($days_exist<-M){
      ($days_exist, $file_name)=(-M, $_);
    }
  }
  print "longest file is $file_name\n";

################## my_perl_track_EX12
#! /usr/bin/perl -w
## Copyright (C) 2013 by Feng GU Truly

#EX12_1_2_3
  print "Please enter your expected path: ";
  chomp(my $path=<STDIN>);
  if($path=~/^\s*$/){
    chdir or die "can't enter into the home directory, $!";
  }else{
    chdir "$path" or die "can't enter into path $path, $!";
  }
  @files = glob ".* *";
  @files = sort @files;
  foreach(@files){
    print $_, "\n";
  }
  opendir FILES, "." or die "can't open the directory, $!";
  foreach(sort readdir FILES){
    print "$_ ";
  }
  print "\n";
  closedir FILES;

###rm simulator
#! /usr/bin/perl -w
## Copyright (C) 2013 by Feng GU Truly

#EX12_4
  my $path="/home/fbgu/src/perl/my_perl_track_EX12/tmp";
  chdir $path or die "can't enter into the home directory, $!";
  foreach $fname(@ARGV){
    if(-e $fname){
      unlink $fname or warn "can't remove this file: $!";
    }else{
      print "file($fname) dont exist\n";
    }
  }
  opendir FILES, "." or die "can't open the directory, $!";
  foreach(readdir FILES){
    print "$_ ";
  }
  print "\n";
  closedir FILES;

###mv simulator
#! /usr/bin/perl -w
## Copyright (C) 2013 by Feng GU Truly

#EX12_5
  my $path="/home/fbgu/src/perl/my_perl_track_EX12/tmp";
  chdir $path or die "can't enter into the home directory, $!";
  use File::Basename;
  use File::Spec;
  $original=shift @ARGV;
  $new=shift @ARGV;
  if(-e $original){
    if(-d $new){
      #my $basename = basename $original;
      #$new = File::Spec->catfile($new, $basename);
      my $bname = $original;
      $new .= "/$bname";
      print "$bname, $new\n";
    }
    if(rename $original, $new){
      print "$original is changed to $new\n";
    }
  }else{
    print "$original is not found\n";
  }
  opendir FILES, "." or die "can't open the directory, $!"

