﻿#include "stdafx.h"
#include "Weapon.h"
#include "Projectile.h"
#include "Fireball.h"

Fireball::Fireball()
{
    this->timeSinceLastTime = 0;

	this->name = "파이어볼";
	this->attackSpeed = 0.8f;

	this->damage = 10.0f;
	this->critical = 0.1;
	
    this->range = 400.0f;
    this->projectileSpeed = 400.f;
}

bool Fireball::Attack()
{
    float currentTime = TIMER->GetWorldTime();
    float elapsedTime = currentTime - lastShotTime;

    if (elapsedTime >= this->timeSinceLastTime)
    {
        // 총구 위치 계산
        Vector2 muzzle = Vector2(
            GM->player->getColliderWeapon()->GetWorldPos() 
            + GM->player->getColliderWeapon()->GetRight() * GM->player->getColliderWeapon()->scale.x);
        // 탄각 계산(플레이어가 바라보는 방향)
        // float rotation_z{ atan2f(shooter->get_right().y, shooter->get_right().x) };

        // 탄생성
        Projectile projectile
        (
            muzzle,
            GM->player->getColliderWeapon()->GetRight(),
            this->projectileSpeed,
            this->range,
            this->damage
        );
        projectile.skin = new ObImage(L"FireballProjectile.png");
        projectile.skin->SetParentRT(*projectile.collider);
        projectile.skin->maxFrame.x = 4;
        projectile.skin->frame.x = 1;
        projectile.skin->scale.x = 32;
        projectile.skin->scale.y = 32;

        //벡터에 탄 push
        GM->player->getProjectiles().emplace_back(projectile);

        // 공속계산
        this->lastShotTime = currentTime;
        this->timeSinceLastTime = 1.0f / this->attackSpeed;
    }

    return false;
}

