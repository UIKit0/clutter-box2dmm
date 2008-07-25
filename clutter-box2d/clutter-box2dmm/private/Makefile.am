## Copyright (c) 2001
## The cluttermm development team.

include $(srcdir)/../../src/Makefile_list_of_hg.am_fragment
files_built_h		= $(files_hg:.hg=_p.h)

private_includedir	= ${includedir}/clutter-box2dmm-$(API_VER)/clutter-box2dmm/private
private_include_HEADERS	= $(files_built_h)

maintainer-clean-local:
	(cd $(srcdir) && rm -f $(files_built_h))

