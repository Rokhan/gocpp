// generated by GoCpp from file '$(ImportDir)/runtime/sigqueue_note.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/sigqueue_note.fwd.h"
#include "gocpp/support.h"

#include "golang/runtime/panic.h"
#include "golang/runtime/runtime2.h"

namespace golang::runtime
{
    void sigNoteSetup(note*);
    void sigNoteSleep(note*);
    void sigNoteWakeup(note*);
}
