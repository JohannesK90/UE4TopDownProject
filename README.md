# UE4TopDownProject

Team 10's Weapon System

Game Reference: Alien Swarm

Weapon types: Shotgun, Rifle, Pistol, Launcher

Implemented systems: 

	Player movement and view from Alien Swarm - Player moves with 'WASD' key in world direction and turns where mouse cursor is. - MyCharacter.h
		
	HUD - HUD widget blueprint is added to viewport by script; Currently, only ammo infomation is shown. - UE4AssignmentGameMode.h

	SFX/VFX - FireSound, ReloadSound and FireEffect are implenmented in scripts. Designers can add their assets in the detail panels. 

	Weapon StartFire : Add a projectile component -> call script event, "StartFire", in blueprint -> call Fire Function from the projectile component - WeaponBase.h
	Weapon EndFire : same way as above. This one is needed to stop auto fire timer. - WeaponBase.h

	Fire System : Made two timer; one for automatic fire, one for fire delay between shots. This prevents projectiles from being fired by spam firing(clicking) - LauncherProjectileComponent.h, ShotgunProjectileComponent.h, SingleFireProjectileComponent.h

	Recoil : Since this game is a top view game, we impleneted recoil system within projectile's fire function by getting random float for shooting direction's yaw value - LauncherProjectileComponent.h, ShotgunProjectileComponent.h, SingleFireProjectileComponent.h

	Reload : implemented typical fps reloading system. weapon pools ammo as much as it lacks in its clip - WeaponBase.h

	Projectile : OnHit - if hit component has a tag named "Enemy", applies point damage. Projectiles are spawned with SpawnActorDeferred function so in this way, the projectile's InitialLifeSpan is modifiable. Projectiles get destroyed out of its weapon's range - Projectile.h

	Interact : Implemented with a interface. Yellow line trace from player's bottom is the interact line trace. When the Line hits a weapon(which inherits the interface), you can interact(equip) by pressing "F" key. - MyCharacter.h

	Weapon Swap : You can drop a weapon by picking up another Weapon. Weapon's collision and physics get disabled when player carries the weapon. - MyCharacter.h

	HealthComponent : HealthComponent is used by DummyTarget. Health value is shown as text above its head. This has TakeDamage function that catches any input damage. - HealthComponent.h

	Easy to make new weapon : Most variables are editable under 'Weapon Info' tap in the detail panel.