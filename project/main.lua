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
    a = allEntities[a]
    b = allEntities[b]
    --[[ more realistic physics work zone
	--normalVector = {x2 - x1, y2 - y1}
	normalX = x2 - x1
	normalY = y2 - y1
	
	unitNormalVector = NormalVector / sqrt((normalX * normalX) + (normalY * normalY))
	unitNormalX = normalX * normalX / ((normalX * normalX) + (normalY * nomralY))
	unitNormalY = normalY * normalY / ((normalX * normalX) + (normalY * nomralY))
	
	unitTangetVector = {-unitNormalY, unitNormalX}
	unitTangentX = -unitNormalY
	unitTangentY = unitNormalX
	
	v1 = {x1,y1}
	v2 = {x2,y2}
	
	velocity1NormalScalar = unitNormalVector . v1
	velocity2NormalScalar = unitNormalVector . v2
	
	velocity1TangentScalar = unitTangentVector . v1
	velocity2TangentScalar = unitTangentVector . v2
	
	finalVelocity1NormalScalar = (velocity1NormalScalar * (mass1 - mass2) + 2 * mass2 * velocity2NormalScalar) / (mass1 + mass2)
	finalVelocity2NormalScalar = (velocity2NormalScalar * (mass2 - mass1) + 2 * mass1 * velocity1NormalScalar) / (mass1 + mass2)
	
	finalVelocity1NormalVector = finalVelocity1NormalScalar * unitNormalVector
	finalVelocity2NormalVector = finalVelocity2NormalScalar * unitNormalVector
	finalVelocity1TangentVector = finalVelocity1TangentScalar * unitTangentVector
	finalVelocity2TangentVector = finalVelocity2TangentScalar * unitTangentVector
	
	velocity1Vector = finalVelocity1NormalVector + finalVelocity1TangentVector
	velocity2Vector = finalVelocity2NormalVector + finalVelocity2TangentVector
	
	]]--
	
	
    -- If an entity has been removed,
    -- it'll come back nil.
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
		   
			--normalVector = {x2 - x1, y2 - y1}
			local normalX = bpx - apx
			local normalY = bpy - apy
			
			--unitNormalVector = NormalVector / sqrt((normalX * normalX) + (normalY * normalY))
			local unitNormalX = normalX * normalX / ((normalX * normalX) + (normalY * normalY))
			local unitNormalY = normalY * normalY / ((normalX * normalX) + (normalY * normalY))
			
			--unitTangetVector = {-unitNormalY, unitNormalX}
			local unitTangentX = -unitNormalY
			local unitTangentY = unitNormalX
			
			--velocityANormalScalar = unitNormalVector . av
			local velocityANormalScalar = unitNormalX * avx + unitNormalY * avy
			--velocityBNormalScalar = unitNormalVector . bv
			local velocityBNormalScalar = unitNormalX * bvx + unitNormalY * bvy
			
			--velocityATangentScalar = unitTangentVector . av
			local velocityATangentScalar = unitTangentX * avx + unitTangentY * avy
			--velocityBTangentScalar = unitTangentVector . bv
			local velocityBTangentScalar = unitTangentX * bvx + unitTangentY * bvy
						
			local am = a.GetMass()
			local bm = b.GetMass()
			
			local finalVelocityANormalScalar = (velocityANormalScalar * (am - bm) + 2 * bm * velocityBNormalScalar) / (am + bm)
			local finalVelocityBNormalScalar = (velocityBNormalScalar * (bm - am) + 2 * am * velocityANormalScalar) / (am + bm)
			
			--finalVelocity1NormalVector = finalVelocityANormalScalar * unitNormalVector
			local finalVelocityANormalX = finalVelocityANormalScalar * unitNormalX
			local finalVelocityANormalY = finalVelocityANormalScalar * unitNormalY
			--finalVelocity2NormalVector = finalVelocityBNormalScalar * unitNormalVector
			local finalVelocityBNormalX = finalVelocityBNormalScalar * unitNormalX
			local finalVelocityBNormalY = finalVelocityBNormalScalar * unitNormalY
			
			--finalVelocity1TangentVector = finalVelocityATangentScalar * unitTangentVector
			local finalVelocityATangentX = velocityATangentScalar * unitTangentX
			local finalVelocityATangentY = velocityATangentScalar * unitTangentY
			--finalVelocity2TangentVector = finalVelocityBTangentScalar * unitTangentVector
			local finalVelocityBTangentX = velocityBTangentScalar * unitTangentX
			local finalVelocityBTangentY = velocityBTangentScalar * unitTangentY
			
			--velocity1Vector = finalVelocity1NormalVector + finalVelocity1TangentVector
			local finalVelocityAX = finalVelocityANormalX + finalVelocityATangentX
			local finalVelocityAY = finalVelocityANormalY + finalVelocityATangentY
			
			--velocity2Vector = finalVelocity2NormalVector + finalVelocity2TangentVector
			local finalVelocityBX = finalVelocityBNormalX + finalVelocityBTangentX
			local finalVelocityBY = finalVelocityBNormalY + finalVelocityBTangentY
			
			--[[local am = a.GetMass()
			local bm = b.GetMass()
			
			local x = apx - bpx
			local y = apy - bpy
			
			local d = x * x + y * y
			
			local nx = x * x / d
			local ny = y * y / d
			
			local p = 2 * (avx * nx + avy * ny - bvx * nx - bvy * ny) / (am + bm)
			
			avx = avx - p * bm * nx
			avy = avy - p * bm * ny
			
			bvx = bvx + p * am * nx
			bvy = bvy + p * am * ny
			
			a.SetVelocity(avx, avy)
			b.SetVelocity(bvx, bvy) ]]--
			
			--[[
			local combinedMass = am + bm
			local differenceMass = am - bm
			
			local bNewVelX = (bvx * differenceMass + (2 * am * avx)) / combinedMass
			local bNewVelY = (bvy * differenceMass + (2 * am * avy)) / combinedMass
			local aNewVelX = (avx * -differenceMass + (2 * bm * bvx)) / combinedMass
			local aNewVelY = (avy * -differenceMass + (2 * bm * bvy)) / combinedMass
		    ]]--
			a.SetVelocity(finalVelocityAX, finalVelocityAY)
			b.SetVelocity(finalVelocityBX, finalVelocityBY)
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

local gr = Nullocity.GetRandom

for i = 1, 16 do
	local size = gr(.5,1.5)
    local entity = NewBaseEntity(size)
    entity.SetPosition(gr(-16, 16), gr(-16, 16))
    entity.SetVelocity(gr(-.5, .5), gr(-.5, .5))
    entity.SetRotation(gr(-135, 135), gr(-135, 135))
    entity.SetTorque(gr(-4, 4), gr(-4, 4))
	
    entity.SetRadius(size * 1.5)
    entity.SetScale(size)
	
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

print('Blam')
