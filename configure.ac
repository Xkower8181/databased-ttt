AC_INIT([databased_ttt], [0.1], [xkowerlolz@gmail.com])

# Safety checks in case user overwritten --srcdir
AC_CONFIG_SRCDIR([src/Projekt_OOP.cpp])
AC_CONFIG_HEADERS([config.h])

# Store the auxiliary build tools (e.g., install-sh, config.sub, config.guess)
# in this dir (build-aux)
AC_CONFIG_AUX_DIR([build-aux])

# Init automake, and specify this program use relaxed structures.
# i.e. this program doesn't follow the gnu coding standards, and doesn't have
# ChangeLog, COPYING, AUTHORS, INSTALL, README etc. files.
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

# Check for Cpp compiler
AC_PROG_CXX
# We can add more checks in this section

# Tells automake to create a Makefile
# See https://www.gnu.org/software/automake/manual/html_node/Requirements.html
AC_CONFIG_FILES([Makefile
                 src/Makefile])

# Generate the output
AC_OUTPUT
