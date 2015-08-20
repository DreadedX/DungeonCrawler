# include "Standard.h"

namespace Audio {

    gau_Manager *mgr = nullptr;
    ga_Mixer *mixer = nullptr;
    ga_StreamManager *streamMgr = nullptr;

    void init() {

	gc_initialize(0);
	mgr = gau_manager_create();
	mixer = gau_manager_mixer(mgr);
	streamMgr = gau_manager_streamManager(mgr);
    }

    void tick() {

	gau_manager_update(mgr);
    }

    void end() {

	gau_manager_destroy(mgr);
	gc_shutdown();
    }

    void test() {

	ga_Handle *handle;
	handle = gau_create_handle_buffered_file(mixer, streamMgr, "audio/jump.wav", "wav", &gau_on_finish_destroy, 0, 0);

	ga_handle_play(handle);
    }

}
