# Report configuration
AC_DEFUN([AC_ENERGON_OUTPUT],
[
    echo
    echo "Package....................... : ${PACKAGE}-${VERSION} for ${host}"
    echo "Build ennet................... : ${enable_ennet}"
    echo "Build enso.................... : ${enable_enso}"
    echo "Build enthread................ : ${enable_enthread}"
    echo "Build enutil.................. : ${enable_enutil}"
    echo "CXX........................... : ${CXX}"
#    echo "CPPFLAGS...................... : ${CPPFLAGS}"
    echo "CXXFLAGS...................... : ${CXXFLAGS}"
#    echo "LDFLAGS....................... : ${LDFLAGS}"
    echo "Debugging enabled............. : $enable_debug"
    echo "Electric fence enabled........ : $enable_efence"
    echo "Profiling enabled............. : $enable_profile"
    echo "Install prefix................ : $prefix"
    echo
    echo "Configure complete, now type 'make'"
    echo
])
