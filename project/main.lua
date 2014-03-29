gr = Nullocity.GetRandom

for i = 1, 8 do
    local n = i * 3
    local entity = Nullocity.AddEntity()
    Nullocity.SetPosition(entity, gr(-16, 16), gr(-16, 16))
    Nullocity.SetVelocity(entity, gr(-1, 1), gr(-1, 1))
    Nullocity.SetRotation(entity, gr(-135, 135), gr(-135, 135))
    Nullocity.SetTorque(entity, gr(-4, 4), gr(-4, 4))
end

io.write('BLAM\n')
