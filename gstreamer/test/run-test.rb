#!/usr/bin/env ruby

# ENV["GST_DEBUG"] = "GST_BUFFER:5"

base_dir = File.expand_path(File.join(File.dirname(__FILE__), ".."))

if system("which make > /dev/null")
  system("cd #{base_dir.dump} && make > /dev/null") or exit(1)
end

glib_dir = File.expand_path(File.join(base_dir, "..", "glib"))
$LOAD_PATH.unshift(glib_dir)
require 'test/glib-test-init'

$LOAD_PATH.unshift(File.join(glib_dir, "src"))
$LOAD_PATH.unshift(File.join(glib_dir, "src", "lib"))

$LOAD_PATH.unshift(File.join(base_dir, "src"))
$LOAD_PATH.unshift(File.join(base_dir, "src", "lib"))
require "gst"

$LOAD_PATH.unshift(File.join(base_dir, "test"))
require 'gst-test-utils'

exit Test::Unit::AutoRunner.run(true)
