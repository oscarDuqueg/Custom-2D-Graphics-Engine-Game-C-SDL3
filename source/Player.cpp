#include "Player.h"


void Player::Shoot()
{
	//Mas de lo mismo, lo comento porque esta to bugeado, es el sonido de cuando disparamos
	//AM->PlaySound("resources/audio/fireball.wav");

	float currentTime = TIME.GetElapsedTime();

	if (currentTime - lastShootTime < shootCooldown)
		return;

	lastShootTime = currentTime;

	//caso base
	Vector2 direction(1.f, 0.f);
	PlayerBullet* bullet = new PlayerBullet(_transform.get(), direction, Vector2(0.f, 0.f));

	SPAWNER.SpawnObject(bullet);

	//PowerUp del cañon
	if (hasTwoCanon && secondCannonFuel > 0)
	{
		Vector2 direction(1.f, 0.f);
		PlayerBullet* sebullet = new PlayerBullet(_transform.get(), direction, Vector2(0.f, 20.f));
		SPAWNER.SpawnObject(sebullet);
		secondCannonFuel -= 5;
	}

	//PowerUp del Laser
	if (hasLaser && laserFuel > 0) {
		Vector2 direction(1.f, 0.f);
		DarkBall* darkball = new DarkBall(_transform.get(), direction);
		SPAWNER.SpawnObject(darkball);
		laserFuel -= 5;;
	}
}

void Player::ApplyRage() {}

void Player::ApplyClone() { hasTwoCanon = true; secondCannonFuel = 200; }

void Player::ApplyPoison() { hasLaser = true; laserFuel = 200; }

void Player::ApplySpeed()
{
	moveSpeed *= 1.35;
}
void Player::ApplyBat()
{
	if (!hasTurrets) {
		UpTurret* upTurret = new UpTurret(this->GetTransform(), Vector2(0.f, -40.f));
		DownTurret* downTurret = new DownTurret(this->GetTransform(), Vector2(0.f, 40.f));

		SPAWNER.SpawnObject(upTurret);
		SPAWNER.SpawnObject(downTurret);

		hasTurrets = true;
	}
}
void Player::ApplyCure()
{
	life = GetMaxLife();
}
