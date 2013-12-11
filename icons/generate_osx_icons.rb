#!/usr/bin/env ruby

require 'fileutils'

RootDir = File.expand_path(File.dirname(__FILE__))
IconFile = File.join(RootDir, 'tomato.svg')
InkscapePath = '/Applications/Inkscape.app/Contents/Resources/bin/inkscape'
IconSet = File.join(RootDir, 'paranolog.iconset')
IcnsFile = File.join(RootDir, 'paranolog.icns')

if `uname -s`.strip() != 'Darwin'
	puts 'This script is supposed to run on Mac OS X only'
	exit 1
end


unless File.executable?(InkscapePath)
	puts 'Inkscape does not seem to be installed on your system, and is required to generate the icons.'
	puts 'Please download Inkscape from http://www.inkscape.org'
end

FileUtils.rm_rf(IconSet, :secure => true)
FileUtils.mkdir_p(IconSet)

def inkscapeCmd(size, suffix = '')
	outPath = File.join(IconSet, "icon_#{size}x#{size}#{suffix}.png")

	return "#{InkscapePath} -z -C --export-height=#{size} --export-width=#{size} --file=#{IconFile} --export-png=#{outPath}"
end

def run(cmd)
	`#{cmd} >/dev/null 2>&1`
	return ($?.exitstatus == 0)
end

[512, 256, 128, 32, 16].each do |size|
	['', '@2x'].each do |suffix|
		factor = (suffix == '@2x' ? 2 : 1)

		puts "Generating icon at size #{size}#{suffix}"

		cmd = inkscapeCmd(size * factor, suffix)

		unless run(cmd)
			puts 'Thumnail generation failed :-('
			puts 'The command was: ' + cmd
			exit 1
		end
	end
end

puts 'Generating icns file'
cmd = "iconutil -c icns -o #{IcnsFile} #{IconSet}"

unless run(cmd)
	puts 'icns file generation failed :-('
	puts 'The command was: ' + cmd
	exit 1
end

FileUtils.rm_rf(IconSet, :secure => true)
