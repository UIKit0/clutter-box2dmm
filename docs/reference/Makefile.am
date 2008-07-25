
doxygen_configfile = Doxyfile
web_path_reference = /home/groups/g/gt/gtkmm/htdocs/gtkmm2DONTUPLOADTHIS/reference

EXTRA_DIST	= README $(doxygen_configfile)


clutter-cairomm-reference: $(doxygen_configfile)
	doxygen $(doxygen_configfile)

clutter-cairomm-reference-html: clutter-cairomm-reference

clutter-cairomm-reference-html.tar.gz: clutter-cairomm-reference-html
	tar -cf - $< | gzip > $@


post-html: clutter-cairomm-reference
	(cd html && tar -cf - *.html *.gif *.css | gzip -3 | \
	 ssh $$SSH_OPT $$USER@gtkmm.sourceforge.net "cd $(web_path_reference)/html ; gunzip | tar -xvf - ; chmod a+r,g+w * ; chgrp gtkmm *")


all-local: clutter-cairomm-reference

clean-local:
	-rm -rf html
	-rm -f clutter-cairomm-reference-html.tar.gz

