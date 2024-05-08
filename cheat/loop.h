#pragma once

namespace Cheat {
	struct AAimbotTarget {
		AFortPawn* player;
		USkeletalMesh* mesh;
		int distance;
		bool visible;
		bool knocked;
	};
	AAimbotTarget* aimbot_target = 0;

	namespace data {
		std::wstring local_weapon;
	}

	int aim_fov = 0;
	float aim_smooth = 0;
	int aim_bone = 0;

	void loop() {
		aimbot_target = 0;
		float aimbot_distance = FLT_MAX;

		int actors_count = 0, actors_visible = 0;

		if (m_width == 0) {
			m_width = canvas->SizeX();
		}

		if (m_height == 0) {
			m_height = canvas->SizeY();
		}

		auto uworld = reinterpret_cast<GWorld*>(*(uintptr_t*)(ptr::gworld));
		if (!uworld) return;

		auto game_state = uworld->GameState();
		if (!game_state) return;

		auto game_instance = uworld->OwningGameInstance();
		if (!game_instance) return;

		auto local_player = game_instance->LocalPlayers()->LocalPlayer();
		if (!local_player) return;

		auto player_controller = local_player->PlayerController();
		if (!player_controller) return;

		if (player_controller->WasInputKeyJustPressed(key::F1))
			c::pickup::enable = !c::pickup::enable;

		if (player_controller->WasInputKeyJustPressed(key::F2))
			c::world::enable = !c::world::enable;

		auto camera_manager = player_controller->PlayerCameraManager();
		if (!camera_manager) return;

		ViewInfo.Location = camera_manager->GetCameraLocation();
		ViewInfo.Rotation = camera_manager->GetCameraRotation();
		ViewInfo.FOV = camera_manager->GetFOVAngle();

		auto local_pawn = player_controller->AcknowledgedPawn();

		auto player_array = game_state->PlayerArray();

		for (int i = 0; i < player_array.size; i++) {
			auto player_state = reinterpret_cast<APlayerState*>(*(uintptr_t*)(player_array.ptr + 0x8 * i));
			if (!player_state) continue;

			if (c::misc::ignore_bots) {
				auto bot = player_state->IsBot();
				if (bot) continue;
			}

			auto player = player_state->PawnPrivate();
			if (!player) continue;

			auto player_team = player_state->TeamIndex();

			if (local_pawn) {
				if (local_pawn == player) continue;

				auto local_team = local_pawn->PlayerState()->TeamIndex();

				if (local_team == player_team) continue;
			}

			auto despawning = player->bIsDespawning();
			if (despawning) continue;

			auto player_mesh = player->Mesh();
			if (!player_mesh) continue;

			actors_count++;

			auto is_visible = player_controller->LineOfSightTo((PVOID)player, ViewInfo.Location);
			auto is_dbno = player->bIsDBNO();

			FLinearColor color = { 1.f, 0.f,0.f, 1.f };
			if (is_dbno) {
				color = { 1.f,1.f,1.f,1.f };
			}
			else if (is_visible) {
				color = {1.f,0.f,0.f,1.f};
				actors_visible++;
			}
			else {
				color = { 1.f, 0.5f ,0.f, 1.f };
			}

			FLinearColor text_color = { 1.f, 1.f, 1.f, 1.f };
			if (c::visuals::allign_text_color) {
				text_color = color;
			}

			auto head_world = player_mesh->GetSocketLocation(Conv_StringToName(_(L"head")));
			auto head_screen = camera_manager->W2S(head_world);

			auto base_world = player_mesh->GetSocketLocation(Conv_StringToName(_(L"root")));
			auto base_screen = camera_manager->W2S(base_world);

			int player_distance = ViewInfo.Location.Distance(base_world) / 100;

			if (c::visuals::enable && (IsInScreen(base_screen) || IsInScreen(head_screen))) {
				int bottom_offset = 10, top_offset = 17;

				if (c::visuals::skeleton) {
				FVector2D vHipOut, vNeckOut, vUpperArmLeftOut, vUpperArmRightOut, vLeftHandOut, vRightHandOut
						, vLeftHandOut1, vRightHandOut1, vRightThighOut, vLeftThighOut, vRightCalfOut, vLeftCalfOut
						, vLeftFootOut, vRightFootOut, PelvisOut;

					FVector vHip = player_mesh->GetSocketLocation(Conv_StringToName(_(L"pelvis")));
					vHipOut = camera_manager->W2S(vHip);

					FVector vNeck = player_mesh->GetSocketLocation(Conv_StringToName(_(L"neck_02")));
					vNeckOut = camera_manager->W2S(vNeck);

					FVector vUpperArmLeft = player_mesh->GetSocketLocation(Conv_StringToName(_(L"upperarm_l")));
					vUpperArmLeftOut = camera_manager->W2S(vUpperArmLeft);

					FVector vUpperArmRight = player_mesh->GetSocketLocation(Conv_StringToName(_(L"upperarm_r")));
					vUpperArmRightOut = camera_manager->W2S(vUpperArmRight);

					FVector vLeftHand = player_mesh->GetSocketLocation(Conv_StringToName(_(L"lowerarm_l")));
					vLeftHandOut = camera_manager->W2S(vLeftHand);

					FVector vRightHand = player_mesh->GetSocketLocation(Conv_StringToName(_(L"lowerarm_r")));
					vRightHandOut = camera_manager->W2S(vRightHand);

					FVector vLeftHand1 = player_mesh->GetSocketLocation(Conv_StringToName(_(L"middle_01_l")));
					vLeftHandOut1 = camera_manager->W2S(vLeftHand1);

					FVector vRightHand1 = player_mesh->GetSocketLocation(Conv_StringToName(_(L"middle_01_r")));
					vRightHandOut1 = camera_manager->W2S(vRightHand1);

					FVector vRightThigh = player_mesh->GetSocketLocation(Conv_StringToName(_(L"thigh_r")));
					vRightThighOut = camera_manager->W2S(vRightThigh);

					FVector vLeftThigh = player_mesh->GetSocketLocation(Conv_StringToName(_(L"thigh_l")));
					vLeftThighOut = camera_manager->W2S(vLeftThigh);

					FVector vRightCalf = player_mesh->GetSocketLocation(Conv_StringToName(_(L"calf_r")));
					vRightCalfOut = camera_manager->W2S(vRightCalf);

					FVector vLeftCalf = player_mesh->GetSocketLocation(Conv_StringToName(_(L"calf_l")));
					vLeftCalfOut = camera_manager->W2S(vLeftCalf);

					FVector vLeftFoot = player_mesh->GetSocketLocation(Conv_StringToName(_(L"ik_foot_l")));
					vLeftFootOut = camera_manager->W2S(vLeftFoot);

					FVector vRightFoot = player_mesh->GetSocketLocation(Conv_StringToName(_(L"ik_foot_r")));
					vRightFootOut = camera_manager->W2S(vRightFoot);

					{
						canvas->K2_DrawLine(FVector2D(vHipOut.X, vHipOut.Y), FVector2D(vNeckOut.X, vNeckOut.Y), c::visuals::skeleton_thickness, color);

						canvas->K2_DrawLine(FVector2D(vUpperArmLeftOut.X, vUpperArmLeftOut.Y), FVector2D(vNeckOut.X, vNeckOut.Y), c::visuals::skeleton_thickness, color);
						canvas->K2_DrawLine(FVector2D(vUpperArmRightOut.X, vUpperArmRightOut.Y), FVector2D(vNeckOut.X, vNeckOut.Y), c::visuals::skeleton_thickness, color);

						canvas->K2_DrawLine(FVector2D(vLeftHandOut.X, vLeftHandOut.Y), FVector2D(vUpperArmLeftOut.X, vUpperArmLeftOut.Y), c::visuals::skeleton_thickness, color);
						canvas->K2_DrawLine(FVector2D(vRightHandOut.X, vRightHandOut.Y), FVector2D(vUpperArmRightOut.X, vUpperArmRightOut.Y), c::visuals::skeleton_thickness, color);

						canvas->K2_DrawLine(FVector2D(vLeftHandOut.X, vLeftHandOut.Y), FVector2D(vLeftHandOut1.X, vLeftHandOut1.Y), c::visuals::skeleton_thickness, color);
						canvas->K2_DrawLine(FVector2D(vRightHandOut.X, vRightHandOut.Y), FVector2D(vRightHandOut1.X, vRightHandOut1.Y), c::visuals::skeleton_thickness, color);

						canvas->K2_DrawLine(FVector2D(vLeftThighOut.X, vLeftThighOut.Y), FVector2D(vHipOut.X, vHipOut.Y), c::visuals::skeleton_thickness, color);
						canvas->K2_DrawLine(FVector2D(vRightThighOut.X, vRightThighOut.Y), FVector2D(vHipOut.X, vHipOut.Y), c::visuals::skeleton_thickness, color);

						canvas->K2_DrawLine(FVector2D(vLeftCalfOut.X, vLeftCalfOut.Y), FVector2D(vLeftThighOut.X, vLeftThighOut.Y), c::visuals::skeleton_thickness, color);
						canvas->K2_DrawLine(FVector2D(vRightCalfOut.X, vRightCalfOut.Y), FVector2D(vRightThighOut.X, vRightThighOut.Y), c::visuals::skeleton_thickness, color);

						canvas->K2_DrawLine(FVector2D(vLeftFootOut.X, vLeftFootOut.Y), FVector2D(vLeftCalfOut.X, vLeftCalfOut.Y), c::visuals::skeleton_thickness, color);
						canvas->K2_DrawLine(FVector2D(vRightFootOut.X, vRightFootOut.Y), FVector2D(vRightCalfOut.X, vRightCalfOut.Y), c::visuals::skeleton_thickness, color);
					}
				}

				head_world.Z += 15;
				auto head_screen_box = camera_manager->W2S(head_world);

				if (c::visuals::box) {
					float box_height = base_screen.Y - head_screen_box.Y;
					float box_width = box_height * 0.4f;

					if (c::visuals::box_outline) {
						canvas->K2_DrawBox({ (base_screen.X - box_width / 2) - 1, (head_screen_box.Y) - 1 }, { box_width, box_height }, c::visuals::box_thickness, { 0.f,0.f,0.f,1.f });
						canvas->K2_DrawBox({ (base_screen.X - box_width / 2) + 1, (head_screen_box.Y) + 1 }, { box_width, box_height }, c::visuals::box_thickness, { 0.f,0.f,0.f,1.f });
					}

					canvas->K2_DrawBox({ base_screen.X - box_width / 2, head_screen_box.Y }, { box_width, box_height }, c::visuals::box_thickness, color);
				}

				if (c::visuals::snapline) {
					canvas->K2_DrawLine(FVector2D(m_width / 2, m_height), FVector2D(base_screen.X, base_screen.Y), 1.5f, color);
				}

				if (c::visuals::distance) {
					const wchar_t* wc1 = crt::to_string(player_distance + 1);
					const wchar_t* wc2 = _(L"m");
					wchar_t wc3[255];

					crt::c_wcscpy(wc3, wc1);
					crt::c_wcscat(wc3, wc2);

					canvas->K2_DrawText({ base_screen.X, base_screen.Y + bottom_offset }, text_color, wc3, { 0.7f, 0.7f });

					bottom_offset += 15;
				}

				if (c::visuals::name) {
					auto name = GetPlayerNameSafe(player);
					if (name.IsValid()) {
						canvas->K2_DrawText({ head_screen_box.X, head_screen_box.Y - top_offset}, text_color, name, { 0.7f,0.7f });
						top_offset += 17;
					}
				}

				if (c::visuals::team_id) {
					const wchar_t* wc1 = _(L"ID: ");
					const wchar_t* wc2 = crt::to_string(player_team);
					wchar_t wc3[255];

					crt::c_wcscpy(wc3, wc1);
					crt::c_wcscat(wc3, wc2);

					canvas->K2_DrawText({ head_screen_box.X, head_screen_box.Y - top_offset }, text_color, wc3, { 0.7f, 0.7f });

					top_offset += 17;
				}

				if (c::visuals::held_weapon) {
					auto weapon = player->Weapon();
					if (weapon) {
						auto data = weapon->WeaponData();
						if (data) {
							FLinearColor weapon_color = { 1.f,1.f,1.f,1.f };

							auto weapon_tier = data->Tier();

							switch (weapon_tier) {
							case EFortItemTier::No_Tier:
								weapon_color = { 1.f,1.f,1.f,1.f };

								break;
							case EFortItemTier::I:
								weapon_color = { 0.4f, 0.4f, 0.4f, 1.f };

								break;
							case EFortItemTier::II:
								weapon_color = { 0.2f, 0.8f, 0.4f, 1.f };

								break;
							case EFortItemTier::III:
								weapon_color = { 0.f, 0.4f, 0.8f, 1.f };

								break;
							case EFortItemTier::IV:
								weapon_color = { 1.f, 0.f, 1.f, 1.f };

								break;
							case EFortItemTier::V:
								weapon_color = { 0.7f, 0.7f, 0.f, 1.f };

								break;
							case EFortItemTier::VI:
								weapon_color = { 1.f, 1.f, 0.f, 1.f };

								break;
							case EFortItemTier::VII:
								weapon_color = { 1.f, 1.f, 0.f, 1.f };

								break;
							}

							const wchar_t* weapon_name = data->DisplayName().Get();

							canvas->K2_DrawText({ base_screen.X, base_screen.Y + bottom_offset }, weapon_color, weapon_name, { 0.7f, 0.7f });

							bottom_offset += 15;
						}
					}
				}
			}

			if (c::aimbot::enable) {
				if (!local_pawn) continue;

				auto build_state = local_pawn->BuildingState();
				if (build_state != EFortBuildingState::None) continue;

				auto weapon = local_pawn->Weapon();
				if (!weapon) continue;

				auto data = weapon->WeaponData();
				if (!data) continue;

				std::wstring name = data->DisplayName().Get();

				if (c::aimbot::weapon) {
					if (name.find(_(L"Pickaxe")) != std::wstring::npos)
						continue;
				}

				data::local_weapon = name;

				if (name.find(_(L"Shotgun")) != std::wstring::npos) {
					aim_fov = c::aimbot::shotgun_fov;
					aim_smooth = c::aimbot::shotgun_smooth;
					aim_bone = c::aimbot::shotgun_aim_bone;
				}
				else if (name.find(_(L"Rifle")) != std::wstring::npos) {
					aim_fov = c::aimbot::rifle_fov;
					aim_smooth = c::aimbot::rifle_smooth;
					aim_bone = c::aimbot::rifle_aim_bone;
				}
				else if (name.find(_(L"SMG")) != std::wstring::npos) {
					aim_fov = c::aimbot::smg_fov;
					aim_smooth = c::aimbot::smg_smooth;
					aim_bone = c::aimbot::smg_aim_bone;
				}
				else {
					aim_fov = c::aimbot::general_fov;
					aim_smooth = c::aimbot::general_smooth;
					aim_bone = c::aimbot::general_aim_bone;
				}

				auto dx = static_cast<float>(head_screen.X - (m_width / 2));
				auto dy = static_cast<float>(head_screen.Y - (m_height / 2));
				auto distance = crt::c_sqrtf(dx * dx + dy * dy);

				if (distance < (aim_fov * 3) && distance < aimbot_distance) {
					aimbot_distance = distance;
					
					AAimbotTarget s_target = { 0 };
					s_target.player = player;
					s_target.mesh = player_mesh;
					s_target.distance = player_distance;
					s_target.visible = is_visible;
					s_target.knocked = is_dbno;

					aimbot_target = &s_target;
				}
			}
		}

		if (c::visuals::enable && c::visuals::render_info) {
			{
				const wchar_t* wc1 = _(L"Enemy Pawns: ");
				const wchar_t* wc2 = crt::to_string(actors_count);
				wchar_t wc3[255];

				crt::c_wcscpy(wc3, wc1);
				crt::c_wcscat(wc3, wc2);

				canvas->K2_DrawText(FVector2D(m_width / 2, 80), { 1.f,0.25f,0.f,1.f }, wc3, {0.85f, 0.85f});
			}
		
			{
				const wchar_t* wc1 = _(L"Visible Pawns: ");
				const wchar_t* wc2 = crt::to_string(actors_visible);
				wchar_t wc3[255];

				crt::c_wcscpy(wc3, wc1);
				crt::c_wcscat(wc3, wc2);

				canvas->K2_DrawText(FVector2D(m_width / 2, 110), { 1.f,0.f,0.f,1.f }, wc3, { 0.85f, 0.85f });
			}
		}

		if (actors_count != 0)
			actors_count = 0;

		if (actors_visible != 0)
			actors_visible = 0;

		if (c::pickup::enable) {
			auto pickup_array = GetAllActorsOfClass(uworld, obj::FortPickup);
			for (int i = 0; i < pickup_array.Num(); i++) {
				if (!pickup_array.IsValidIndex(i)) continue;

				auto pickup_tmp = reinterpret_cast<AFortPawn*>(pickup_array[i]);
				if (!pickup_tmp) continue;

				auto pickup_location = pickup_tmp->RootComponent()->RelativeLocation();
				auto pickup_distance = ViewInfo.Location.Distance(pickup_location) / 100;
				if (pickup_distance > c::pickup::distance) continue;

				auto pickup_screen = camera_manager->W2S(pickup_location);

				if (IsInScreen(pickup_screen)) {
					auto pickup = reinterpret_cast<APickup*>(pickup_tmp);

					auto definition = pickup->GetItemDefinition();

					auto tier = definition->Tier();

					if (tier == EFortItemTier::No_Tier) continue;

					FLinearColor color = {};

					if (c::pickup::uncommon && tier == EFortItemTier::I)
						color = { 0.4f, 0.4f, 0.4f , 1.f};
					else if (c::pickup::common && tier == EFortItemTier::II)
						color = { 0.2f, 0.8f, 0.4f , 1.f};
					else if (c::pickup::rare && tier == EFortItemTier::III)
						color = { 0.f, 0.4f, 0.8f , 1.f};
					else if (c::pickup::epic && tier == EFortItemTier::IV)
						color = { 1.f, 0.f, 1.f , 1.f};
					else if (c::pickup::legendary && tier == EFortItemTier::V)
						color = { 0.7f, 0.7f, 0.f , 1.f};
					else if (c::pickup::mythic && tier == EFortItemTier::VI)
						color = { 1.f, 1.f, 0.f , 1.f};
					else if (c::pickup::exotic && tier == EFortItemTier::VII)
						color = { 0.f, 0.8f, 1.f , 1.f};
					else continue;

					if (c::pickup::show_distance) {
						std::wstring name = definition->DisplayName().Get();

						std::wstring result = name + std::wstring(_(L" [")) + std::wstring(crt::to_string((int)pickup_distance)) + std::wstring(_(L"m]"));

						canvas->K2_DrawText(pickup_screen, color, result.c_str(), {0.65f, 0.65f});
					}
					else {
						auto name = definition->DisplayName().Get();
						canvas->K2_DrawText(pickup_screen, color, name, { 0.65f, 0.65f });
					}
				}
			}
		}

		if (c::world::enable) {
			auto container_array = GetAllActorsOfClass(uworld, obj::BuildingContainer);
			for (int i = 0; i < container_array.Num(); i++) {
				if (!container_array.IsValidIndex(i)) continue;
				auto container_actor = (AFortPawn*)container_array[i];
				if (!IsPtrValid(container_actor)) continue;

				auto container_location = container_actor->RootComponent()->RelativeLocation();
				auto container_distance = ViewInfo.Location.Distance(container_location) / 100;
				if (container_distance > c::world::distance) continue;

				auto already_searched = *(bool*)(container_actor + 0xf82);
				if (already_searched) continue;

				auto container_w2s = camera_manager->W2S(container_location);

				if (IsInScreen(container_w2s)) {
					auto container = (UObject*)container_actor;
					auto object_str = GetObjectName(container);

					if (ObjectContains(object_str.c_str(), _(L"Tiered_Chest"), false, false) && c::world::chest) {
						if (c::world::show_distance) {
							std::wstring result = std::wstring(_(L"Chest")) + std::wstring(_(L" [")) + std::wstring(crt::to_string((int)container_distance)) + std::wstring(_(L"m]"));
							canvas->K2_DrawText(container_w2s, FLinearColor(1.f, 1.f, 0.f, 1.f), result.c_str(), { 0.7f, 0.7f });
						}
						else {
							canvas->K2_DrawText(container_w2s, FLinearColor(1.f, 1.f, 0.f, 1.f), _(L"Chest"));
						}
					}
					else if (ObjectContains(object_str.c_str(), _(L"Tiered_Ammo"), false, false) && c::world::ammo_box) {
						if (c::world::show_distance) {
							std::wstring result = std::wstring(_(L"AmmoBox")) + std::wstring(_(L" [")) + std::wstring(crt::to_string((int)container_distance)) + std::wstring(_(L"m]"));
							canvas->K2_DrawText(container_w2s, FLinearColor(0.3f, 1.f, 0.f, 1.f), result.c_str(), { 0.7f, 0.7f });
						}
						else {
							canvas->K2_DrawText(container_w2s, FLinearColor(0.3f, 1.f, 0.f, 1.f), _(L"Ammo Box"));
						}
					}
					else if (ObjectContains(object_str.c_str(), _(L"Cooler_Container"), false, false) && c::world::cooler) {
						if (c::world::show_distance) {
							std::wstring result = std::wstring(_(L"Cooler")) + std::wstring(_(L" [")) + std::wstring(crt::to_string((int)container_distance)) + std::wstring(_(L"m]"));
							canvas->K2_DrawText(container_w2s, FLinearColor(0.f, 0.5f, 1.f, 1.f), result.c_str(), { 0.7f, 0.7f });
						}
						else {
							canvas->K2_DrawText(container_w2s, FLinearColor(0.f, 0.5f, 1.f, 1.f), _(L"Cooler Box"));
						}
					}
				}
			}
		}

		if (c::aimbot::enable && c::aimbot::draw_fov) {
			canvas->DrawCircle(m_width / 2, m_height / 2, aim_fov * 3, 30, { 1.f, 1.f, 1.f, 1.f });
		}

		if (!local_pawn || !aimbot_target) return;

		if (c::aimbot::enable) {
			auto player = aimbot_target->player;
			auto mesh = aimbot_target->mesh;
			auto distance = aimbot_target->distance;
			auto visible = aimbot_target->visible;
			auto knocked = aimbot_target->knocked;

			if (c::aimbot::visible)
				if (!visible) return;

			if (c::aimbot::knocked)
				if (knocked) return;

			FVector bone_location = { 0,0,0 };
			
			if (aim_bone == 0) {
				bone_location = mesh->GetSocketLocation(Conv_StringToName(_(L"head")));
			}
			else if (aim_bone == 1) {
				bone_location = mesh->GetSocketLocation(Conv_StringToName(_(L"neck_01")));
			}
			else if (aim_bone == 2) {
				bone_location = mesh->GetSocketLocation(Conv_StringToName(_(L"spine_05")));
			}
			else {
				auto head_location = mesh->GetSocketLocation(Conv_StringToName(_(L"head")));
				auto neck_location = mesh->GetSocketLocation(Conv_StringToName(_(L"neck_01")));
				auto chest_location = mesh->GetSocketLocation(Conv_StringToName(_(L"spine_05")));

				auto head_screen = camera_manager->W2S(head_location);
				auto neck_screen = camera_manager->W2S(neck_location);
				auto chest_screen = camera_manager->W2S(chest_location);

				float dx = 0;
				float dy = 0;

				dx = head_screen.X - (m_width / 2); dy = head_screen.Y - (m_height / 2);
				auto head_distance = crt::c_sqrtf(dx * dx + dy * dy);

				dx = neck_screen.X - (m_width / 2); dy = neck_screen.Y - (m_height / 2);
				auto neck_distance = crt::c_sqrtf(dx * dx + dy * dy);

				dx = chest_screen.X - (m_width / 2); dy = chest_screen.Y - (m_height / 2);
				auto chest_distance = crt::c_sqrtf(dx * dx + dy * dy);

				if (head_distance <= neck_distance && head_distance <= chest_distance) {
					bone_location = head_location;
				}
				else if (neck_distance <= head_distance && neck_distance <= chest_distance) {
					bone_location = neck_location;
				}
				else {
					bone_location = chest_location;
				}
			}

			if (c::aimbot::draw_line) {
				auto screen = camera_manager->W2S(bone_location);

				canvas->K2_DrawLine(screen, FVector2D(m_width / 2, m_height / 2), 1.f, { 1.f,1.f,1.f,1.f });
			}

			FKey aim_key = {};
			switch (c::aimbot::key) {
			case 0:
				aim_key = key::LeftMouseButton;
				break;
			case 1:
				aim_key = key::RightMouseButton;
				break;
			case 2:
				aim_key = key::LeftControl;
				break;
			case 3:
				aim_key = key::LeftShift;
				break;
			case 4:
				aim_key = key::Enter;
				break;
			}

			FVector current_rot = ViewInfo.Rotation;
			FVector calc = CalcAngle(ViewInfo.Location, bone_location);
			Normalise(calc);

			FVector delta = calc - current_rot;
			Normalise(delta);

			delta.X = delta.X / aim_smooth;
			delta.Y = delta.Y / aim_smooth;

			if (player_controller->IsInputKeyDown(aim_key)) {
				
			}
		}
	}
}