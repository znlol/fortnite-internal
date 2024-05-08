#pragma once
#include <Windows.h>
#include <vector>
#include <string>
#include <winternl.h>
#include <Psapi.h>
#include <locale>
#include <algorithm>
#include <intrin.h>

#include "util/importer.h"
#include "util/xorstr.h"
#include "util/util.h"
#include "util/crt.h"

#include "spoof/ret.h"

#include "defines/vars.h"

#include "hook/vmt.h"

#include "memory/man.h"

#include "defines/config.h"

#include "engine/offsets.h"
#include "engine/enums.h"
#include "engine/structs.h"
#include "engine/classes.h"
#include "engine/vars.h"
#include "engine/functions.h"
#include "engine/impl.h"

#include "cheat/load.h"
#include "cheat/loop.h"

#include "render/framework.h"
#include "render/menu.h"