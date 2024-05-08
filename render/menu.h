#pragma once

namespace Render {
	bool show_menu = true;

	void menu() {
		ZeroGUI::SetupCanvas(canvas);
		ZeroGUI::Input::Handle();

		if (GetAsyncKeyState(VK_INSERT) & 1)
			show_menu = !show_menu;

		static FVector2D pos = FVector2D(400, 200);

		if (ZeroGUI::Window(_("vario (throwback edition)"), &pos, { 650, 370 }, show_menu)) {
			static int tab = 0;

			if (ZeroGUI::ButtonTab(_("Aimbot"), { 145, 28 }, tab == 0)) tab = 0;
			ZeroGUI::SameLine();
			if (ZeroGUI::ButtonTab(_("Visuals"), { 145, 28 }, tab == 1)) tab = 1;
			ZeroGUI::SameLine();
			if (ZeroGUI::ButtonTab(_("World"), { 145, 28 }, tab == 2)) tab = 2;
			ZeroGUI::SameLine();
			if (ZeroGUI::ButtonTab(_("Misc"), { 145, 28 }, tab == 3)) tab = 3;

			if (tab == 0) {
				ZeroGUI::PushNextElementY(5);

				ZeroGUI::Text(_("General :"));
				ZeroGUI::Checkbox(_("Enable"), &c::aimbot::enable);
				ZeroGUI::Checkbox(_("Draw FOV Circle"), &c::aimbot::draw_fov);
				ZeroGUI::Checkbox(_("Draw Target Line"), &c::aimbot::draw_line);
				ZeroGUI::Checkbox(_("Engine Prediction"), &c::aimbot::prediction);
				ZeroGUI::Checkbox(_("Target Visible"), &c::aimbot::visible);
				ZeroGUI::Checkbox(_("Ignore Knocked"), &c::aimbot::knocked);
				ZeroGUI::Checkbox(_("Weapon Check"), &c::aimbot::weapon);
				ZeroGUI::SliderAimkey(_("Aimbot Key"), &c::aimbot::key, 0, 4);

				ZeroGUI::NextColumn(300);
				ZeroGUI::PushNextElementY(-227);

				ZeroGUI::Text(_("Advanced :"));

				static int weapon_cb = 0;
				ZeroGUI::SliderWeaponConfig(_("Selected Weapon"), &weapon_cb, 0, 3);

				if (weapon_cb == 0) {
					ZeroGUI::SliderInt(_("Shotgun FOV"), &c::aimbot::shotgun_fov, 1, 500);
					ZeroGUI::SliderFloat(_("Shotgun Smooth"), &c::aimbot::shotgun_smooth, 1.f, 40.f);
					ZeroGUI::SliderAimBone(_("Shotgun Bone"), &c::aimbot::shotgun_aim_bone, 0, 3);
				}
				else if (weapon_cb == 1) {
					ZeroGUI::SliderInt(_("Rifle FOV"), &c::aimbot::rifle_fov, 1, 500);
					ZeroGUI::SliderFloat(_("Rifle Smooth"), &c::aimbot::rifle_smooth, 1.f, 40.f);
					ZeroGUI::SliderAimBone(_("Rifle Bone"), &c::aimbot::rifle_aim_bone, 0, 3);
				}
				else if (weapon_cb == 2) {
					ZeroGUI::SliderInt(_("SMG FOV"), &c::aimbot::smg_fov, 1, 500);
					ZeroGUI::SliderFloat(_("SMG Smooth"), &c::aimbot::smg_smooth, 1.f, 40.f);
					ZeroGUI::SliderAimBone(_("SMG Bone"), &c::aimbot::smg_aim_bone, 0, 3);
				}
				else {
					ZeroGUI::SliderInt(_("General FOV"), &c::aimbot::general_fov, 1, 500);
					ZeroGUI::SliderFloat(_("General Smooth"), &c::aimbot::general_smooth, 1.f, 40.f);
					ZeroGUI::SliderAimBone(_("General Bone"), &c::aimbot::general_aim_bone, 0, 3);
				}

			}
			else if (tab == 1) {
				ZeroGUI::PushNextElementY(5);

				ZeroGUI::Text(_("Player :"));
				ZeroGUI::Checkbox(_("Enable Visuals"), &c::visuals::enable);
				ZeroGUI::Checkbox(_("Draw Snapline"), &c::visuals::snapline);
				ZeroGUI::Checkbox(_("Draw Box"), &c::visuals::box);
				ZeroGUI::Checkbox(_("Draw Skeleton"), &c::visuals::skeleton);
				ZeroGUI::Checkbox(_("Draw Distance"), &c::visuals::distance);
				ZeroGUI::Checkbox(_("Draw Name"), &c::visuals::name);
				ZeroGUI::Checkbox(_("Draw Team ID"), &c::visuals::team_id);
				ZeroGUI::Checkbox(_("Draw Held Weapon"), &c::visuals::held_weapon);
				ZeroGUI::Checkbox(_("Draw Render Info"), &c::visuals::render_info);

				ZeroGUI::NextColumn(300);
				ZeroGUI::PushNextElementY(-267);

				ZeroGUI::Text(_("Misc :"));
				ZeroGUI::Checkbox(_("Allign Text Color"), &c::visuals::allign_text_color);
				ZeroGUI::Checkbox(_("Outlined Box"), &c::visuals::box_outline);
				ZeroGUI::SliderFloat(_("Box Thickness"), &c::visuals::box_thickness, 1.f, 4.f);
				ZeroGUI::SliderFloat(_("Skeleton Thickness"), &c::visuals::skeleton_thickness, 1.f, 4.f);
				ZeroGUI::SliderInt(_("ESP Distance"), &c::visuals::limit, 1, 500);
			}
			else if (tab == 2) {
				ZeroGUI::PushNextElementY(5);

				ZeroGUI::Text(_("Pickup [F1] :"));
				ZeroGUI::Checkbox(_("Enable "), &c::pickup::enable);
				ZeroGUI::Checkbox(_("Show Distance"), &c::pickup::show_distance);
				ZeroGUI::Checkbox(_("Uncommon"), &c::pickup::uncommon);
				ZeroGUI::Checkbox(_("Common"), &c::pickup::common);
				ZeroGUI::Checkbox(_("Rare"), &c::pickup::rare);
				ZeroGUI::Checkbox(_("Epic"), &c::pickup::epic);
				ZeroGUI::Checkbox(_("Legendary"), &c::pickup::legendary);
				ZeroGUI::Checkbox(_("Mythic"), &c::pickup::mythic);
				ZeroGUI::Checkbox(_("Exotic"), &c::pickup::exotic);
				ZeroGUI::SliderInt(_("Pickup Distance"), &c::pickup::distance, 1, 500);

				ZeroGUI::NextColumn(300);
				ZeroGUI::PushNextElementY(-267);

				ZeroGUI::Text(_("World [F2] :"));
				ZeroGUI::Checkbox(_("Enable "), &c::world::enable);
				ZeroGUI::Checkbox(_("Show Distance"), &c::world::show_distance);
				ZeroGUI::Checkbox(_("Llama"), &c::world::llama);
				ZeroGUI::Checkbox(_("Chest"), &c::world::chest);
				ZeroGUI::Checkbox(_("Ammo Box"), &c::world::ammo_box);
				ZeroGUI::Checkbox(_("Cooler"), &c::world::cooler);
				ZeroGUI::Checkbox(_("Vehicle"), &c::world::vehicle);
				ZeroGUI::SliderInt(_("World Distance"), &c::world::distance, 1, 3000);
			}
			else if (tab == 3) {
				ZeroGUI::PushNextElementY(5);

				ZeroGUI::Text(_("Misc :"));
				ZeroGUI::Checkbox(_("Ignore Bots"), &c::misc::ignore_bots);
				ZeroGUI::Checkbox(_("Disable Smooth [Snipers]"), &c::misc::disable_sniper_smooth);
				ZeroGUI::SliderInt(_("W2S"), &c::misc::W2S, 200, 500);
			}
		}

		ZeroGUI::DrawCursor(show_menu);
		ZeroGUI::Render();
	}
}