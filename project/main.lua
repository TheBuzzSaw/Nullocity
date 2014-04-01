allEntities = {}

function FixPosition(entity)
    local px, py = entity.GetPosition()
    local vx, vy = entity.GetVelocity()
    
    local changed = false
    local n = 16
    
    if vx > 0 and px > n then
        px = px - n - n
        changed = true
    elseif vx < 0 and px < -n then
        px = px + n + n
        changed = true
    end
    
    if vy > 0 and py > n then
        py = py - n - n
        changed = true
    elseif vy < 0 and py < -n then
        py = py + n + n
        changed = true
    end
    
    if changed then
        entity.SetPosition(px, py)
    end
end

function OnUpdate()
    for _, v in pairs(allEntities) do
        FixPosition(v)
    end
end

function OnCollision(a, b)
    entityA = allEntities[a]
    entityB = allEntities[b]
    
    -- If an entity has been removed,
    -- it'll come back nil.
    if entityA and entityB then
        local avx, avy = entityA.GetVelocity()
        local bvx, bvy = entityB.GetVelocity()
		
        local apx, apy = entityA.GetPosition()
        local bpx, bpy = entityB.GetPosition()		
	
		if CheckAxisCollision(avx, bvx, apx, bpx) or CheckAxisCollision(avy, bvy, apy, bpy) then
			local am = entityA.GetMass()
			local bm = entityB.GetMass()
			
			aMomx = avx * am
			aMomy = avy * am
			bMomx = bvx * bm
			bMomy = bvy * bm
		
		
			entityA.SetVelocity(bMomx / am, bMomy / am)
			entityB.SetVelocity(aMomx / bm, aMomy / bm)
		end
    end
end

function CheckAxisCollision(av, bv, ap, bp)

	if bp < ap then
		if (bv - av) > 0 then
			return true
		end
		return false
	else
		if (bv - av) < 0 then
			return true
		end
		return false
	end
end

function NewBaseEntity(mass)
    local self = { entity = Nullocity.AddEntity(), mass = mass }
    
    local Remove = function()
            allEntities[self.entity] = nil
            Nullocity.RemoveEntity(self.entity)
        end
    
    local SetPosition = function(x, y)
            Nullocity.SetPosition(self.entity, x, y)
        end
    
    local SetVelocity = function(x, y)
            Nullocity.SetVelocity(self.entity, x, y)
        end
    
    local SetRotation = function(x, y)
            Nullocity.SetRotation(self.entity, x, y)
        end
        
    local SetTorque = function(x, y)
            Nullocity.SetTorque(self.entity, x, y)
        end
        
    local SetRadius = function(radius)
            Nullocity.SetRadius(self.entity, radius)
        end
        
    local SetScale = function(scale)
            Nullocity.SetScale(self.entity, scale)
        end
		
	local SetMass = function(mass)
			self.mass = mass;
		end
        
    local GetPosition = function()
            return Nullocity.GetPosition(self.entity)
        end
        
    local GetVelocity = function()
            return Nullocity.GetVelocity(self.entity)
        end
        
    local GetRotation = function()
            return Nullocity.GetRotation(self.entity)
        end
        
    local GetTorque = function()
            return Nullocity.GetTorque(self.entity)
        end
        
    local GetRadius = function()
            return Nullocity.GetRadius(self.entity)
        end
        
    local GetScale = function()
            return Nullocity.GetScale(self.entity)
        end

    local GetMass = function() return self.mass end
    
    local result = {
        Remove = Remove,
        SetPosition = SetPosition,
        SetVelocity = SetVelocity,
        SetRotation = SetRotation,
        SetTorque = SetTorque,
        SetRadius = SetRadius,
        SetScale = SetScale,
		SetMass = SetMass,
		GetPosition = GetPosition,
		GetVelocity = GetVelocity,
		GetRotation = GetRotation,
		GetTorque = GetTorque,
		GetRadius = GetRadius,
		GetScale = GetScale,
        GetMass = GetMass }
    
    allEntities[self.entity] = result
    
    return result
end

function Debug()
    print("--- Entity Position Dump ---")
    for _, v in pairs(allEntities) do
        print(v.GetPosition())
    end
end

function GenerateRandomAsteroids()
	gr = Nullocity.GetRandom

	for i = 1, 16 do
		local size = gr(.5,1.5)
		local entity = NewBaseEntity(size)
		entity.SetPosition(gr(-16, 16), gr(-16, 16))
		entity.SetVelocity(gr(-.5, .5), gr(-.5, .5))
		entity.SetRotation(gr(-135, 135), gr(-135, 135))
		entity.SetTorque(gr(-4, 4), gr(-4, 4))
		
		entity.SetRadius(size * 1.25)
		entity.SetScale(size)
		
		print("Size is: ", size)
		
		print("Position: ", entity.GetPosition())
		print("Velocity: ", entity.GetVelocity())
		print("Rotation: ", entity.GetRotation())
		print("Torque: ", entity.GetTorque())
		print("Radius: ", entity.GetRadius())
		print("Scale: ", entity.GetScale())
	end
end

asteroidA = NewBaseEntity(1)
asteroidA.SetPosition(2,0)
asteroidA.SetVelocity(0,0)

asteroidB = NewBaseEntity(1)
asteroidB.SetPosition(-2,0)
asteroidB.SetVelocity(.5,0)
	
Nullocity.SetCollisionCallback(OnCollision)
Nullocity.SetUpdateCallback(OnUpdate)

print('Blam')
