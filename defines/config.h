#pragma once

namespace c {
	namespace aimbot {
		bool enable = false;
		bool draw_fov = false;
		bool draw_line = false;
		bool prediction = false;
		bool visible = false;
		bool knocked = false;
		bool weapon = false;

		int general_fov = 45;
		float general_smooth = 7.f;
		int general_aim_bone = 2;

		int rifle_fov = 45;
		float rifle_smooth = 6.f;
		int rifle_aim_bone = 1;

		int shotgun_fov = 95;
		float shotgun_smooth = 2.5f;
		int shotgun_aim_bone = 0;

		int smg_fov = 60;
		float smg_smooth = 5.f;
		int smg_aim_bone = 1;

		int key = 2;
	}

	namespace visuals {
		bool enable = true;

		bool snapline = false;
		bool box = true;
		bool skeleton = false;
		bool distance = false;
		bool name = false;
		bool team_id = false;
		bool held_weapon = false;
		bool render_info = false;

		bool allign_text_color = false;
		bool box_outline = false;

		float box_thickness = 2.f;
		float skeleton_thickness = 2.f;

		int limit = 350;
	}

	namespace pickup {
		bool enable = false;
		bool show_distance = false;
		bool uncommon = false;
		bool common = false;
		bool rare = false;
		bool epic = false;
		bool legendary = false;
		bool mythic = false;
		bool exotic = false;

		int distance = 50;
	}

	namespace world {
		bool enable = false;
		bool show_distance = false;
		bool llama = false;
		bool chest = false;
		bool ammo_box = false;
		bool cooler = false;
		bool vehicle = false;

		int distance = 200;
	}

	namespace misc {
		bool ignore_bots = true;
		bool disable_sniper_smooth = false;
		int W2S = 360;
	}
}