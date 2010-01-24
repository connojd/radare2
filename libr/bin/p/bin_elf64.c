/* radare - GPL3 - Copyright 2009 nibble<.ds@gmail.com> */

#define R_BIN_ELF64 1
#include "bin_elf.c"

static int check(struct r_bin_t *bin)
{
	ut8 *buf;
	int ret = R_FALSE;

	if (!(buf = (ut8*)r_file_slurp_range(bin->file, 0, 5)))
		return R_FALSE;
	/* buf[EI_CLASS] == ELFCLASS64 */
	if (!memcmp(buf, "\x7F\x45\x4c\x46\x02", 4))
		ret = R_TRUE;
	free(buf);
	return ret;
}

struct r_bin_handle_t r_bin_plugin_elf64 = {
	.name = "elf64",
	.desc = "elf64 bin plugin",
	.init = NULL,
	.fini = NULL,
	.new = &pnew,
	.free = &pfree,
	.check = &check,
	.baddr = &baddr,
	.entry = &entry,
	.sections = &sections,
	.symbols = &symbols,
	.imports = &imports,
	.strings = NULL,
	.info = &info,
	.fields = &fields,
};

#ifndef CORELIB
struct r_lib_struct_t radare_plugin = {
	.type = R_LIB_TYPE_BIN,
	.data = &r_bin_plugin_elf64
};
#endif
