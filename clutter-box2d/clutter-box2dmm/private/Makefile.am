## Copyright (c) 2001
## The cluttermm development team.

include $(srcdir)/../../src/Makefile_list_of_hg.am_fragment
files_built_h		= $(files_hg:.hg=_p.h)

private_includedir	= ${includedir}/clutter-cairomm-$(API_VER)/clutter-cairomm/private
private_include_HEADERS	= $(files_built_h)

maintainer-clean-local:
	(cd $(srcdir) && rm -f $(files_built_h))

