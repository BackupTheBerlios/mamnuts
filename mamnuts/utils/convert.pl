#!/usr/bin/perl

#=-------------------------------------------------------------------
#= Filename: convert.pl
#= Author  : Mind Booster Noori, marcos.marado@sonae.com
#=
#= Created : 21th October, 2006
#= Revised : 28th October, 2006
#= Version : 1.0
#=
#= This program allows you to convert your user files from NUTS 3.3.3
#= to Mamnuts 1.8.3.  This will only convert standard NUTS files - 
#= ie, ones that you have not added any extra strings to.
#=-------------------------------------------------------------------
#= This is mostly original code, but is inspired (even this header!) 
#= from Andy's convert.pl that converts NUTS 3.3.3 files into Amnuts 
#= 1.4.1 ones. The code is almost completely different, but it's 
#= never too much to leave credit where credit is due ;-) This script 
#= is public domain, but please consider leaving authorship as well 
#= as this credit to Andy if you're pondering on distributing a 
#= version of this file. Thanks! 
#=-------------------------------------------------------------------
#= Tested only with perl version 5.8.8 so I apologize if it doesn't
#= work on any other versions.
#=-------------------------------------------------------------------

$userdir='./old-userfiles';  # where they are located relative to prog.

opendir(DIR,$userdir) || die "Can't open $userdir: $!\n";
local(@filenames) = readdir(DIR);
closedir(DIR);

@filenames=sort(@filenames);

# Get list of all .D user files
foreach $file (@filenames) {
    if ($file=~/\.D/) {
	$file=~s/\.D//;
	push(@users,$file);
    }
}
undef(@filenames);


# Alter the actual userfiles
$count=0;
foreach $name (@users) {
    chomp($name);
    open(FPI,"$userdir/$name.D") || die "Could not load userfile $name: $!\n";
    @lines=<FPI>;
    close(FPI);
    open(FPO,">tempuser") || die "Could not open temphelp: $!\n";

    # 1st line is version
    print FPO "version\t0.1\n";
    
    # 2nd line is the password
    print FPO "password\t".$lines[4];

    # 3rd line is the date he was promoted
    print FPO "promote_date\ton Saturday 1st January 2006 at 00:00pm\n";

    # 4th line is various time information
    print FPO "times\t1162080016 10 3 1162080005\n";

    # 5th line is the level
    # we increment level since now there's JAILED...
    chomp ($lines[3]);
    print FPO "levels\t".++$lines[3]." ".$lines[3]." 0 0 0\n";

    # 6th line is general stuff
    print FPO "general\t0 0 0 1 1 0 0 1\n";

    #7th line is user settings
    print FPO "user_set\t0 0 0 99 1 0 0 0 0 0 1 0 #UNSET 0\n";

    #8th line is user ignores
    print FPO "user_ignores\t0 0 0 0 0 0 0 0\n";

    #9th line is purging info: I hope you have autopurge off after this...
    print FPO "purging\t1 0\n";

    #10th line is last site and last room
    print FPO "last_site\tprevious.version.of.talker reception\n";

    #11th line is mail
    print FPO "mail_verify\t#UNSET\n";

    #12th line is description
    chomp ($lines[2]);
    if (length($lines[2]) > '24') {
        print FPO "description\ttem de mudar de .desc!\n";
    } else {
        print FPO "description\t".$lines[2]."\n";
    }

    #13th in phrase
    print FPO "in_phrase\tenters\n";

    #14th out phrase
    print FPO "out_phrase\tgoes\n";
   
    #15th email
    print FPO "email\t#UNSET\n";

    #16th homepage
    print FPO "homepage\t#UNSET\n";

    #17th recap
    print FPO "recap_name\t$name\n";

    #18th games
    print FPO "games\t0 0 0 0 6 10 1012 3000\n";

    rename("tempuser","$userdir/$name.D");
    print "Converted = $name.D\n";
    ++$count;
}

print "Altered -=[ $count ]=- user files.\n";
