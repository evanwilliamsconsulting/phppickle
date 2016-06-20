<?php
ini_set('memory_limit','1024M');
$zope = new PHPZope();

$zope->readPickle("/usr/local/apache2/phpzope/newdoc.txt");

$zo = $zope->returnPickleFile();

foreach ($zo as $item=>$zo1)
{
	if ($item != "theMemo")
        {
		print $item;
		print_r($zo1);
		print "<br/>";
	}
	else
	{
		print "<br/>";
		print $item;
		print "<br/>";
		foreach ($zo1 as $index => $test)
		{
			print $index;
			print_r($test);
			print "<br/>";
		}
	}
}
?>
