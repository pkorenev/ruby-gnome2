#!/usr/bin/env ruby

=begin
Sample script using Gtk::Socket and Gtk::Plug.
Written by Alex Boussinet <mailto:dbug@wanadoo.fr> for testing purpose only.
=end

require 'gtk'

class MyGtkPlug
	def initialize(xid, plug)
		plug = "Button" if plug.nil?
		if xid.nil?
			@window = Gtk::Window.new Gtk::WINDOW_TOPLEVEL
			@window.set_title "Gtk::Plug Test"
			@window.set_default_size 250, 50
		else
			@window = Gtk::Plug.new xid.to_i
		end
		@window.set_policy true, true, false
		@window.set_position Gtk::WIN_POS_CENTER
		@window.signal_connect "delete_event" do Gtk::main_quit end
		@vbox = Gtk::VBox.new true, 5
		@window.add @vbox
		@button1 = Gtk::Button.new plug
		@button1.signal_connect "clicked" do $stderr.puts plug end
		@button2 = Gtk::Button.new "Exit"
		@button2.signal_connect "clicked" do Gtk::main_quit end
		# Exit button to test an unexpected end of child process by Gtk::Socket
		@vbox.add @button1
		@vbox.add @button2
		@window.show_all
	end
end

xid = nil
ARGV.each_index { |i|
	arg = ARGV.at i
	if arg =~ "-x"
		if arg.length > 2
			xid = arg[2..-1]
		else
			xid = ARGV.at i+1
			ARGV.delete_at i+1
		end
		xid = nil if xid.to_i <= 0
		ARGV.delete_at i
	end 
}
MyGtkPlug.new(xid, ARGV.shift)
Gtk::main
