local gr = Nullocity.GetRandom
local arenaRadius = 64

entitiesByHandle = {}
cameraEntity = nil

function FixPosition(entity)
    local px, py = entity.GetPosition()
    local vx, vy = entity.GetVelocity()
    local radius = entity.GetRadius()
    
    local changed = false
    local n = arenaRadius
    
    local high = px + radius
    local low = px - radius
    
    if vx > 0 and high > n then
        px = n + n - high - radius
        vx = -vx
        changed = true
    elseif vx < 0 and low < -n then
        px = -low + radius - n - n
        vx = -vx
        changed = true
    end
    
    high = py + radius
    low = py - radius
    
    if vy > 0 and high > n then
        py = n + n - high - radius
        vy = -vy
        changed = true
    elseif vy < 0 and low < -n then
        py = -low + radius - n - n
        vy = -vy
        changed = true
    end
    
    if changed then
        entity.SetPosition(px, py)
        entity.SetVelocity(vx, vy)
        entity.SetTorque(gr(-4, 4), gr(-4, 4))
    end
end

function OnUpdate()
    for _, v in pairs(entitiesByHandle) do
        FixPosition(v)
    end
    
    local x, y = cameraEntity.GetPosition()
    Nullocity.SetCameraPosition(x, y, 0)
end

function OnCollision(a, b)
    a = entitiesByHandle[a]
    b = entitiesByHandle[b]
    
    -- If an entity has been removed, it'll come back nil.
    if a and b then
        local avx, avy = a.GetVelocity()
        local bvx, bvy = b.GetVelocity()
		
		local xVel = bvx - avx
		local yVel = bvy - avy
		
        local apx, apy = a.GetPosition()
        local bpx, bpy = b.GetPosition()
		
		local xDist = apx - bpx
		local yDist = apy - bpy
	
		local dotProduct = xDist*xVel + yDist*yVel
	
		if dotProduct > 0 then
		
			local am = a.GetMass()
			local bm = b.GetMass()
			
			local combinedMass = am + bm
			local differenceMass = am - bm
			
			
			local bNewVelX = (bvx * differenceMass + (2 * am * avx)) / combinedMass
			local bNewVelY = (bvy * differenceMass + (2 * am * avy)) / combinedMass
			local aNewVelX = (avx * -differenceMass + (2 * bm * bvx)) / combinedMass
			local aNewVelY = (avy * -differenceMass + (2 * bm * bvy)) / combinedMass
			
			local amx = avx * am
			local amy = avy * am
			local bmx = bvx * bm
			local bmy = bvy * bm
		
			a.SetVelocity(aNewVelX, aNewVelY)
			b.SetVelocity(bNewVelX, bNewVelY)
			
			a.SetTorque(gr(-4, 4), gr(-4, 4))
			b.SetTorque(gr(-4, 4), gr(-4, 4))
		end
    end
end

function CheckAxisCollision(av, bv, ap, bp)
    local result = false
    
	if bp < ap then
		if (bv - av) > 0 then
			result = true
		end
	else
		if (bv - av) < 0 then
			result = true
		end
	end
    
    return result
end

function NewBaseEntity(mass)
    local self = { entity = Nullocity.AddEntity(), mass = mass }
    
    local Remove = function()
            entitiesByHandle[self.entity] = nil
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
    
    entitiesByHandle[self.entity] = result
    
    return result
end

function Debug()
    print("--- Entity Position Dump ---")
    for _, v in pairs(entitiesByHandle) do
        print(v.GetPosition())
    end
end

for i = 1, 128 do
	local size = gr(.5,1.5)
    local entity = NewBaseEntity(size)
    entity.SetPosition(gr(-arenaRadius, arenaRadius),
        gr(-arenaRadius, arenaRadius))
    entity.SetVelocity(gr(-.5, .5), gr(-.5, .5))
    entity.SetRotation(gr(-135, 135), gr(-135, 135))
    entity.SetTorque(gr(-4, 4), gr(-4, 4))
	
    entity.SetRadius(size * 1.25)
    entity.SetScale(size)
    
    if not cameraEntity then cameraEntity = entity end
	
	print("Size is: ", size)
	
	print("Position: ", entity.GetPosition())
	print("Velocity: ", entity.GetVelocity())
	print("Rotation: ", entity.GetRotation())
	print("Torque: ", entity.GetTorque())
	print("Radius: ", entity.GetRadius())
	print("Scale: ", entity.GetScale())
end

Nullocity.SetCollisionCallback(OnCollision)
Nullocity.SetUpdateCallback(OnUpdate)

