allEntities = {}

function OnCollision(a, b)
    entityA = allEntities[a]
    entityB = allEntities[b]
    
    -- If an entity has been removed,
    -- it'll come back nil.
    if entityA and entityB then
        ax, ay = entityA.GetVelocity()
        bx, by = entityB.GetVelocity()
	
        entityA.SetVelocity(bx, by)
        entityB.SetVelocity(ax, ay)
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

    local Mass = function() return self.mass end
    
    local result = {
        Remove = Remove,
        SetPosition = SetPosition,
        SetVelocity = SetVelocity,
        SetRotation = SetRotation,
        SetTorque = SetTorque, 
		GetPosition = GetPosition,
		GetVelocity = GetVelocity,
		GetRotation = GetRotation,
		GetTorque = GetTorque,
        Mass = Mass }
    
    allEntities[self.entity] = result
    
    return result
end

function Debug()
    print("--- Entity Position Dump ---")
    for _, v in pairs(allEntities) do
        print(v.GetPosition())
    end
end

gr = Nullocity.GetRandom

for i = 1, 16 do
    local entity = NewBaseEntity(i)
    entity.SetPosition(gr(-16, 16), gr(-16, 16))
    entity.SetVelocity(gr(-.5, .5), gr(-.5, .5))
    entity.SetRotation(gr(-135, 135), gr(-135, 135))
    entity.SetTorque(gr(-4, 4), gr(-4, 4))
	
	print("Position: ", entity.GetPosition())
	print("Velocity: ", entity.GetVelocity())
	print("Rotation: ", entity.GetRotation())
	print("Torque: ", entity.GetTorque())
end

Nullocity.SetCollisionCallback(OnCollision)

io.write('BLAM\n')
