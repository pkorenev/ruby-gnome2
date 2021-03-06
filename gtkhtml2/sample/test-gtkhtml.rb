=begin
  test-gtkhtml.rb - Gtk::Html sample script.

  Copyright (C) 2003-2006 Ruby-GNOME2 Project Team
  This program is licenced under the same licence as Ruby-GNOME2.

  $Id: test-gtkhtml.rb,v 1.6 2006/06/17 14:23:40 mutoh Exp $
=end

require 'gtkhtml2'

window = Gtk::Window.new("Gtk::Html sample")

window.signal_connect( "destroy" ) {
   Gtk.main_quit
}

window.border_width = 10
window.set_default_size(200, 200)

htmlview = Gtk::HtmlView.new()
htmlview.show

window.add(htmlview)
window.show_all

doc = Gtk::HtmlDocument.new()
doc.open_stream('text/html')
doc.write_stream('<html><body><h1>TEST 2</h1>HtmlDocument test</br>\
    <a href="foo">link test foo</a>\
    <a href="bar">link test bar</a>\
    </body></html>')
doc.close_stream()

doc.signal_connect( "link_clicked" ) {  |doc,link|
    puts "link_clicked #{link}"
    htmlview.document.clear
    htmlview.document.open_stream("text/html")
    htmlview.document.write_stream( "<html><body><h1>#{link}</h1></body></html>")
    htmlview.document.close_stream()
}

##### sample handler for 'request_url' signal might look like this
##### (you need this to show images inside the widget)
#doc.signal_connect('request_url') { |html_doc, url, stream|
#   puts "request_url #{html_doc} #{url} #{stream}"
#   File.open( File.expand_path(url) ) {|file| #TODO: here add argument for base_url
#     puts "open success"
#     data = file.read()
#     stream.write(data)
#     stream.close()
#   }
#}

htmlview.document = doc

Gtk.main

