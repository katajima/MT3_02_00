#include <Novice.h>
#include<cmath>
#include<assert.h>
#include<Functions.h>
#include<imgui.h>

const char kWindowTitle[] = "LE2B_06_カタジマ_ロウノシン_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	//移動
	Vector3 translate{};
	//回転
	Vector3 rotate{};
	//カメラポジション
	Vector3 cameraPosition{ 0.0f,15.9f,-61.49f };
	Vector3 cameraRotate{ 0.26f,0.0f,0.0f };
	//線分
	Segment segment{ {-2.0f,-1.0f,0.0f},{3.0f,2.0f,2.0f} };
	//Segment segment2{ { -3.0f,2.0f,1.0f }, { 2.0f,4.0f,4.0f } };

	//
	Vector3 point{ -1.5f,0.6f,0.6f };
	//Vector3 point2{ 1.0f,0.0f,0.0f };

	//正射影ベクトル
	Vector3 project = Project(Subtract(point, segment.origin), segment.diff);
	//Vector3 project3 = Project(segment2.origin, segment2.diff);
	//最近接点
	Vector3 closestPoint = ClosestPoint(point, segment);

	Sphere pointSphere{ point,0.03f };// 1cmの球を描画
	Sphere closestPointSphere{ closestPoint,0.03f };
	

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///


		if (keys[DIK_LEFT]) {
			cameraPosition.x -= 2;

		}
		if (keys[DIK_RIGHT]) {
			cameraPosition.x += 2;

		}
		if (keys[DIK_W]) {
			cameraPosition.y += 0.3f;

		}
		if (keys[DIK_S]) {
			cameraPosition.y -= 0.3f;

		}
		if (keys[DIK_UP]) {
			cameraPosition.z += 2;

		}
		if (keys[DIK_DOWN]) {
			cameraPosition.z -= 2;

		}

		Matrix4x4 worldMatrix = MakeAffineMatrixMatrix({ 1.0f,1.0f,1.0f }, rotate, translate);

		Matrix4x4 cameraMatrix = MakeAffineMatrixMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraPosition);

		Matrix4x4 viewMatrix = Inverse(cameraMatrix);

		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(1280) / float(720), 0.1f, 100.0f);

		Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));

		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(1280), float(720), 0.0f, 1.0f);


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		//グリッド線
		DrawGrid(worldViewProjectionMatrix, viewportMatrix);

		//球
		DrawSphere(pointSphere, worldViewProjectionMatrix, viewportMatrix, RED);
		DrawSphere(closestPointSphere, worldViewProjectionMatrix, viewportMatrix, BLACK);

		//線
		Vector3 start = Transform(Transform(segment.origin, worldViewProjectionMatrix), viewportMatrix);
		Vector3 end = Transform(Transform(Add(segment.origin, segment.diff), worldViewProjectionMatrix), viewportMatrix);
		Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), WHITE);
		
		

		ImGui::Begin("Window");
		ImGui::DragFloat3("CameraTranslate", &cameraPosition.x, 0.01f);
		ImGui::DragFloat3("cameraRotate", &cameraRotate.x, 0.01f);
		ImGui::InputFloat3("project", &project.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
		ImGui::InputFloat3("segment.origin", &segment.origin.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
		ImGui::InputFloat3("segment.diff", &segment.diff.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
		ImGui::InputFloat3("point", &point.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
		ImGui::End();

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
