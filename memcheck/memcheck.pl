#!/usr/bin/perl

$fname="testfile.txt";

open TEST_FILE, $fname or die "Can't find the specified file!!!";

$index=0;
$correct=0;
while(<TEST_FILE>){
  print $_ if $index % 2 == 0;
  if($index % 2 == 1){
    $input=<STDIN>; 
    if($input ne $_){
      chomp($_);
      print "The Answer should be [$_]\n"; 
    }else{
      print "Correct!!!\n";
      $correct++;
    }
  }
  $index++;
}

$total= $index/2;
$score= ($correct/$total)*100;
print "**********************************
*    Total   : $total
*    Correct : $correct
*    score   : $score
**********************************
";
