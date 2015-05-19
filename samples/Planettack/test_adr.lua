print ("BEGIN")
function Spacecraft (self)
  local cobj = GObj:new(self.model)
  cobj:setName(self.name)
  MainScene:addObject(cobj:getName(), cobj)
  cobj:setAnimationState (self.state)

  local skl = self.skills

  for i=1, #skl do
    print(skl[i])
  end

  local stp = self.steps
  for i=1, #stp do
    cobj:addStep(stp[i].x, stp[i].y, stp[i].z)
  end

  return cobj
end

local enemies = {
  Spacecraft{
    name = "ship1",
    model = "models/robot.mesh",
    state = "Walk",
    skills = {"knife", "axe"},
    steps = {
      {x = 0, y= 0, z = 0},
      {x = 220, y= 0, z = 320},
      {x = 320, y= 0, z = 70},
      {x = -20, y= 0, z = -40}
    }
  },
  Spacecraft{
    name = "ship2",
    model = "models/robot.mesh",
    state = "Idle",
    skills = {"knife", "axe"},
    steps = {
      {x = 0, y= 0, z = 0},
      {x = 120, y= 0, z = 420},
      {x = 20, y= 0, z = 32},
      {x = 0, y= 0, z = 0},
      {x = -120, y= 0, z = -70}
    }
  },
  Spacecraft{
    name = "ship3",
    model = "models/robot.mesh",
    state = "Idle",
    skills = {"knife", "axe"},
    steps = {
      {x = 0, y= 0, z = 0},
      {x = -120, y= 0, z = -420},
      {x = -20, y= 0, z = -32},
      {x = 0, y= 0, z = 0},
      {x = 120, y= 0, z = 70}
    }
  }  
}

local Hero = Spacecraft {
  name = "hero",
  model = "models/robot.mesh",
  state = "Idle",
  skills = {"knife", "axe"},
  steps = {
    {x = 0, y= 0, z = 0},
    {x = 120, y= 0, z = 230},
    {x = 0, y= 0, z = 0},
    {x = 14, y= 0, z = 43},
    {x = -120, y= 0, z = 40}
  }
}

--MainScene:addObject(Hero:getName(), Hero)

--for i=1, #enemies do
--  MainScene:addObject(enemies[i]:getName(), enemies[i])
--end

--while LControl:Alive() do
--  for i, obj in ipairs(enemies) do
--    obj:Move();
--  end
--end

print ("FIM")

