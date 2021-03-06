--------------------------------------------------
-- Episode code for every level
-- Created @DATETIME@
--------------------------------------------------
@ONLOAD{

-- Run code on level loading by game engine before initalizing stuff
-- (CAREFULLY USE IT! Use it to initialize own variables
-- and don't process any operations with any objects and states of the level or world map!
-- Use onStart() for those purposes instead this).
function onLoad()
    --Your code here
end
@}
@ONSTART{

-- Run code on the first frame
function onStart()
    --Your code here
end
@}
@ONTICK{

-- Run code every frame (~1/65 second)
-- (code will be executed before game logic will be processed)
function onTick()
    --Your code here
end
@}
@ONTICKEND{

-- Run code every frame (~1/65 second)
-- (code will be executed after game logic will be processed)
function onTickEnd()
    --Your code here
end
@}
@ONDRAW{

-- This is called just before drawing each frame
function onDraw()
    --Your code here
end
@}
@ONEVENT{

-- Run code when internal event of the SMBX Engine has been triggered
-- eventName - name of triggered event
function onEvent(eventName)
    --Your code here
end
@}


