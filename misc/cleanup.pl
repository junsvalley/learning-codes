#!/usr/bin/perl

@files = 501..700;
$head = "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">
<html xmlns=\"http://www.w3.org/1999/xhtml\">
<body>
<div id=\"wrapper\">
	<div class=\"content_read\">
		<div class=\"box_con\">
			<div class=\"bookname\">";

$tail = "		</div>
	</div>
</div>
</body>
</html>";

@lines = qw{$head};

foreach $i(@files) {
    $file="file".$i.".html";
    open FILE_HTML, $file or die "Can't open file $file\n";
    while(<FILE_HTML>) {
      if(m#<h1>.*</h1>#) {
        push @lines, $_;
        push @lines, "</div>";
      }
      elsif(m#<div id="content">.*</div>#) {
        push @lines, $_;
      }
    }
}

push @lines, $tail;

print @lines;

