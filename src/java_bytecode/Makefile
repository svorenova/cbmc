SRC = bytecode_info.cpp \
      character_refine_preprocess.cpp \
      ci_lazy_methods.cpp \
      ci_lazy_methods_needed.cpp \
      expr2java.cpp \
      jar_file.cpp \
      java_bytecode_convert_class.cpp \
      java_bytecode_convert_method.cpp \
      java_bytecode_instrument.cpp \
      java_bytecode_internal_additions.cpp \
      java_bytecode_language.cpp \
      java_bytecode_parse_tree.cpp \
      java_bytecode_parser.cpp \
      java_bytecode_typecheck.cpp \
      java_bytecode_typecheck_code.cpp \
      java_bytecode_typecheck_expr.cpp \
      java_bytecode_typecheck_type.cpp \
      java_class_loader.cpp \
      java_class_loader_limit.cpp \
      java_entry_point.cpp \
      java_local_variable_table.cpp \
      java_object_factory.cpp \
      java_pointer_casts.cpp \
      java_root_class.cpp \
      java_string_library_preprocess.cpp \
      java_types.cpp \
      java_utils.cpp \
      mz_zip_archive.cpp \
      select_pointer_type.cpp \
      # Empty last line

INCLUDES= -I ..

include ../config.inc
include ../common

CLEANFILES = java_bytecode$(LIBEXT)

all: java_bytecode$(LIBEXT)

###############################################################################

java_bytecode$(LIBEXT): $(OBJ)
	$(LINKLIB)
