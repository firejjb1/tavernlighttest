Jump = {}

jumpButton = nil
jumpWindow = nil

movingButton = nil
curX = 0
maxMarginX = 250
buttonOffsetYs = {[0]=0, 100, 200, 150, 250 }
curYIndex = 0

function init()
  jumpButton = modules.client_topmenu.addRightGameToggleButton('jumpButton', 
    tr('Jump') .. ' (Ctrl+J)', '/images/topbuttons/minimap', toggle)
  jumpButton:setOn(true)
  jumpWindow = g_ui.displayUI('jump.otui')

  movingButton = jumpWindow:getChildById("movingButton")
  connect(g_game, { onOpenJumpWindow = Jump.create,
                    onGameEnd = Jump.destroy })
end

function terminate()
  disconnect(g_game, { onOpenJumpWindow = Jump.create,
                       onGameEnd = Jump.destroy })
  Jump.destroy()
  
end

function onJumpButtonClick()
    curX = 0
    curYIndex = (curYIndex + 1 ) % 5
    movingButton:setMarginRight(0)
    movingButton:setMarginTop(buttonOffsetYs[curYIndex])
    movingButton:setMoveToX(maxMarginX)
end 

function Jump.create(spellList)
  Jump.destroy()

  jumpWindow = g_ui.displayUI('jump.otui')
end

function Jump.destroy()
  if jumpWindow then
    jumpWindow:destroy()
    jumpButton:destroy()
    jumpWindow = nil
  end
end

function toggle()
    if jumpButton:isOn() then
        jumpWindow:close()
        jumpButton:setOn(false)
    else
        jumpWindow:open()
      jumpButton:setOn(true)
    end
  end