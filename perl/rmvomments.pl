use strict;
my $incomment = 0; 
my $if        = 0; 
my @newlines  = {};
my $linecnt   = 0;
my @srclines  = <>;
my $onesrcline= "";
my @seplines  = {};
foreach(@srclines){
	chomp($_);
	$onesrcline .= $_."LINE_SEPERATE";
}
#print "$onesrcline\n";

$onesrcline =~ s/\/\*(.*?)\*\///g;
#print "$onesrcline\n";

@seplines = split "LINE_SEPERATE", $onesrcline;

foreach(@seplines){         #remove #if 0 ...  #endif 
  $linecnt++; 
  next if (/^\s*\/\/.*$/); #// comments
  if (/^\s*#if\w*\s+(\w+)/) 
  { 
      $if++; 
      $incomment = $if if ($1 eq '0' && (!$incomment)); 
  } 
  elsif (/^\s*#endif\s*/) 
  { 
      $incomment = 0, next if ($if-- == $incomment); 
  } 
  $_ .= "\n";
  push @newlines, $_ if (!$incomment); 
}
print "@newlines\n";

