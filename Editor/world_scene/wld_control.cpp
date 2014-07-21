/*
 * Platformer Game Engine by Wohlstand, a free platform for game making
 * Copyright (c) 2014 Vitaly Novichkov <admin@wohlnet.ru>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QtMath>

#include "wld_scene.h"
#include "../edit_world/world_edit.h"

#include "item_tile.h"
#include "item_scene.h"
#include "item_path.h"
#include "item_level.h"
#include "item_music.h"


#include "../common_features/mainwinconnect.h"
#include "../common_features/grid.h"
#include "wld_item_placing.h"

#include "../file_formats/file_formats.h"


QPoint WsourcePos=QPoint(0,0);
int WgridSize=0, WoffsetX=0, WoffsetY=0;//, gridX, gridY, i=0;


void WldScene::keyReleaseEvent ( QKeyEvent * keyEvent )
{
    QList<QGraphicsItem*> selectedList = selectedItems();
    WorldData historyBuffer;
    bool deleted=false;

    QString objType;
    switch(keyEvent->key())
    {
    case (Qt::Key_Delete): //Delete action
        if(selectedList.isEmpty()) break;

        for (QList<QGraphicsItem*>::iterator it = selectedList.begin(); it != selectedList.end(); it++)
        {

                objType=(*it)->data(0).toString();

                if(!(*it)->isVisible()) continue;  //Invisible items can't be deleted

                //remove data from main array before deletion item from scene
                if( objType=="TILE" )
                {
                    historyBuffer.tiles.push_back(((ItemTile *)(*it))->tileData);
                    ((ItemTile *)(*it))->removeFromArray();
                    if((*it)) delete (*it);
                    deleted=true;
                }
                else
                if( objType=="SCENERY" )
                {
                    historyBuffer.scenery.push_back(((ItemScene*)(*it))->sceneData);
                    ((ItemScene *)(*it))->removeFromArray();
                    if((*it)) delete (*it);
                    deleted=true;
                }
                else
                if( objType=="PATH" )
                {
                    historyBuffer.paths.push_back(((ItemPath*)(*it))->pathData);
                    ((ItemPath *)(*it))->removeFromArray();
                    if((*it)) delete (*it);
                    deleted=true;
                }
                else
                if( objType=="LEVEL" )
                {
                    historyBuffer.levels.push_back(((ItemLevel*)(*it))->levelData);
                    ((ItemLevel *)(*it))->removeFromArray();
                    if((*it)) delete (*it);
                    deleted=true;
                }
//                else
//                if( objType=="MUSICBOX" )
//                {
//                    historyBuffer.music.push_back(((ItemMusic*)(*it))->musicData);
//                    ((ItemMusic *)(*it))->removeFromArray();
//                    if((*it)) delete (*it);
//                    deleted=true;
//                }

        }
        //dummy
        if(deleted) historyBuffer.scenery.size();//addRemoveHistory(historyBuffer);

        break;
    case (Qt::Key_Escape):
        if(!IsMoved)
            this->clearSelection();
//        if(pResizer!=NULL )
//        {
//            switch(pResizer->type)
//            {
//            case 3:
//                setPhysEnvResizer(NULL, false, false);
//                break;
//            case 2:
//                setBlockResizer(NULL, false, false);
//                break;
//            case 1:
//                setEventSctSizeResizer(-1, false, false);
//                break;
//            case 0:
//            default:
//                MainWinConnect::pMainWin->on_cancelResize_clicked();
//            }
//        }
            //setSectionResizer(false, false);
        break;
//    case (Qt::Key_Enter):
//    case (Qt::Key_Return):

//        if(pResizer!=NULL )
//        {
//            switch(pResizer->type)
//            {
//            case 3:
//                setPhysEnvResizer(NULL, false, true);
//                break;
//            case 2:
//                setBlockResizer(NULL, false, true);
//                break;
//            case 1:
//                setEventSctSizeResizer(-1, false, true);
//                break;
//            case 0:
//            default:
//                MainWinConnect::pMainWin->on_applyResize_clicked();
//            }
//        }
//            //setSectionResizer(false, true);
//        break;

    default:
        break;
    }
    QGraphicsScene::keyReleaseEvent(keyEvent);
}

void WldScene::openProps()
{
//    QList<QGraphicsItem * > items = this->selectedItems();
//    if(!items.isEmpty())
//    {
//        if(items.first()->data(0).toString()=="Block")
//        {
//            MainWinConnect::pMainWin->LvlItemProps(0,
//                          ((ItemBlock *)items.first())->blockData,
//                          FileFormats::dummyLvlBgo(),
//                          FileFormats::dummyLvlNpc(), false);
//        }
//        else
//        if(items.first()->data(0).toString()=="BGO")
//        {
//            MainWinConnect::pMainWin->LvlItemProps(1,
//                              FileFormats::dummyLvlBlock(),
//                              ((ItemBGO *)items.first())->bgoData,
//                              FileFormats::dummyLvlNpc(), false);
//        }
//        else
//        if(items.first()->data(0).toString()=="NPC")
//        {
//            MainWinConnect::pMainWin->LvlItemProps(2,
//                              FileFormats::dummyLvlBlock(),
//                              FileFormats::dummyLvlBgo(),
//                              ((ItemNPC *)items.first())->npcData, false);
//        }
//        else
//        MainWinConnect::pMainWin->LvlItemProps(-1,
//                                               FileFormats::dummyLvlBlock(),
//                                               FileFormats::dummyLvlBgo(),
//                                               FileFormats::dummyLvlNpc());
//    }
//    else
//    {
//        MainWinConnect::pMainWin->LvlItemProps(-1,
//                                               FileFormats::dummyLvlBlock(),
//                                               FileFormats::dummyLvlBgo(),
//                                               FileFormats::dummyLvlNpc());
//    }

//    QGraphicsScene::selectionChanged();
}

void WldScene::selectionChanged()
{
//    if(this->selectedItems().isEmpty())
//    {
//        LevelBlock dummyBlock;
//        dummyBlock.array_id=0;

//        LevelBGO dummyBgo;
//        dummyBgo.array_id=0;

//        LevelNPC dummyNPC;
//        dummyNPC.array_id=0;

//        MainWinConnect::pMainWin->LvlItemProps(-1, dummyBlock, dummyBgo, dummyNPC);
//    }

    #ifdef _DEBUG_
    WriteToLog(QtDebugMsg, "Selection Changed!");
    #endif
}

static QPointF drawStartPos = QPoint(0,0);

void WldScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    #ifdef _DEBUG_
    WriteToLog(QtDebugMsg, QString("Mouse pressed -> [%1, %2] contextMenuOpened=%3, DrawMode=%4").arg(mouseEvent->scenePos().x()).arg(mouseEvent->scenePos().y())
               .arg(contextMenuOpened).arg(DrawMode));
    #endif

if(contextMenuOpened) return;

    switch(EditingMode)
    {
        case MODE_PlacingNew:
        {
            if( mouseEvent->buttons() & Qt::RightButton )
            {
                MainWinConnect::pMainWin->on_actionSelect_triggered();
                return;
            }

            if(cursor){
                cursor->setPos( QPointF(applyGrid( mouseEvent->scenePos().toPoint()-
                                                   QPoint(WldPlacingItems::c_offset_x,
                                                          WldPlacingItems::c_offset_y),
                                                   WldPlacingItems::gridSz,
                                                   WldPlacingItems::gridOffset)));
            }
            placeItemUnderCursor();
            QGraphicsScene::mousePressEvent(mouseEvent);
            return;
            break;
        }
        case MODE_DrawSquare:
        {
            if( mouseEvent->buttons() & Qt::RightButton )
            {
                MainWinConnect::pMainWin->on_actionSelect_triggered();
                return;
            }

            if(cursor){
                drawStartPos = QPointF(applyGrid( mouseEvent->scenePos().toPoint(),
                                                  WldPlacingItems::gridSz,
                                                  WldPlacingItems::gridOffset));
                cursor->setPos( drawStartPos );
                cursor->setVisible(true);

                QPoint hw = applyGrid( mouseEvent->scenePos().toPoint(),
                                       WldPlacingItems::gridSz,
                                       WldPlacingItems::gridOffset);

                QSize hs = QSize( (long)fabs(drawStartPos.x() - hw.x()),  (long)fabs( drawStartPos.y() - hw.y() ) );
                ((QGraphicsRectItem *)cursor)->setRect(0,0, hs.width(), hs.height());
            }

            QGraphicsScene::mousePressEvent(mouseEvent);
            return;
            break;

        }
        case MODE_Resizing:
        {
            QGraphicsScene::mousePressEvent(mouseEvent);
            return;
        }
        case MODE_Erasing:
        {
            if( mouseEvent->buttons() & Qt::RightButton )
            {
                MainWinConnect::pMainWin->on_actionSelect_triggered();
                return;
            }

            if(cursor){
               cursor->show();
               cursor->setPos(mouseEvent->scenePos());
            }

            QGraphicsScene::mousePressEvent(mouseEvent);

            QList<QGraphicsItem*> selectedList = selectedItems();
            if (!selectedList.isEmpty())
            {
                removeItemUnderCursor();
                EraserEnabled=true;
            }
            break;
        }
        case MODE_PasteFromClip: //Pasta
        {
            if( mouseEvent->buttons() & Qt::RightButton )
            {
                MainWinConnect::pMainWin->on_actionSelect_triggered();
                return;
            }
            PasteFromBuffer = true;
            break;
        }
        default:
        {
            if((disableMoveItems) && (mouseEvent->buttons() & Qt::LeftButton)
                && (Qt::ControlModifier != QApplication::keyboardModifiers()))
            { return; }

            QGraphicsScene::mousePressEvent(mouseEvent);

            break;
        }
    }
    haveSelected=(!selectedItems().isEmpty());

}


void WldScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    //WriteToLog(QtDebugMsg, QString("Mouse moved -> [%1, %2]").arg(mouseEvent->scenePos().x()).arg(mouseEvent->scenePos().y()));
    if(contextMenuOpened) return;

    switch(EditingMode)
    {
    case MODE_PlacingNew:
        {
            this->clearSelection();
            if(cursor)
            {
                        cursor->setPos( QPointF(applyGrid( mouseEvent->scenePos().toPoint()-
                                                           QPoint(WldPlacingItems::c_offset_x,
                                                                  WldPlacingItems::c_offset_y),
                                                         WldPlacingItems::gridSz,
                                                         WldPlacingItems::gridOffset)));
                       cursor->show();
            }
            if( mouseEvent->buttons() & Qt::LeftButton ) placeItemUnderCursor();
            QGraphicsScene::mouseMoveEvent(mouseEvent);
            break;
        }
    case MODE_DrawSquare:
        {
            if(cursor)
            {
                if(cursor->isVisible())
                {
                QPoint hw = applyGrid( mouseEvent->scenePos().toPoint(),
                                       WldPlacingItems::gridSz,
                                       WldPlacingItems::gridOffset);

                QSize hs = QSize( (long)fabs(drawStartPos.x() - hw.x()),  (long)fabs( drawStartPos.y() - hw.y() ) );


                ((QGraphicsRectItem *)cursor)->setRect(0,0, hs.width(), hs.height());
                ((QGraphicsRectItem *)cursor)->setPos(
                            ((hw.x() < drawStartPos.x() )? hw.x() : drawStartPos.x()),
                            ((hw.y() < drawStartPos.y() )? hw.y() : drawStartPos.y())
                            );
                }
            }
        }
    case MODE_Resizing:
        {
            this->clearSelection();
            QGraphicsScene::mouseMoveEvent(mouseEvent);
            return;
        break;
        }
    case MODE_Erasing:
        {
            if(cursor) cursor->setPos(mouseEvent->scenePos());
            if (EraserEnabled)// Remove All items, placed under Cursor
                removeItemUnderCursor();
            break;
        }
    default:
        if(cursor) cursor->setPos(mouseEvent->scenePos());
        break;
    }

    haveSelected=(!selectedItems().isEmpty());
    if(haveSelected)
    {
        if(!IsMoved)
        {
            IsMoved = true;
        }
    }
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void WldScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(contextMenuOpened)
    {
        contextMenuOpened = false; //bug protector
        QGraphicsScene::mouseReleaseEvent(mouseEvent);
        return;
    }

    switch(EditingMode)
    {
    case MODE_DrawSquare:
        {

        if(cursor)
        {

            // /////////// Don't draw with zero width or height //////////////
            if( (((QGraphicsRectItem *)cursor)->rect().width()==0) ||
              (((QGraphicsRectItem *)cursor)->rect().height()==0))
            {
                cursor->hide();
                break;
            }
            // ///////////////////////////////////////////////////////////////

            switch(placingItem)
            {
            case PLC_Tile:
                {
                    long x = cursor->scenePos().x();
                    long y = cursor->scenePos().y();
                    long width = ((QGraphicsRectItem *)cursor)->rect().width();
                    long height = ((QGraphicsRectItem *)cursor)->rect().height();
                    int repWidth = width/WldPlacingItems::itemW;
                    int repHeight = height/WldPlacingItems::itemH;

                    WorldData plSqTile;
                    for(int i = 0; i < repWidth; i++){
                        for(int j = 0; j < repHeight; j++){
                            WldPlacingItems::TileSet.x = x + i * WldPlacingItems::itemW;
                            WldPlacingItems::TileSet.y = y + j * WldPlacingItems::itemH;

                            WldData->tile_array_id++;

                            WldPlacingItems::TileSet.array_id = WldData->tile_array_id;

                            WldData->tiles.push_back(WldPlacingItems::TileSet);
                            placeTile(WldPlacingItems::TileSet, true);
                            plSqTile.tiles.push_back(WldPlacingItems::TileSet);
                        }
                    }
                    if(plSqTile.tiles.size() > 0)
                    {
                        //addPlaceHistory(plSqBgo);
                    }
                }
            case PLC_Scene:
                {
                    long x = cursor->scenePos().x();
                    long y = cursor->scenePos().y();
                    long width = ((QGraphicsRectItem *)cursor)->rect().width();
                    long height = ((QGraphicsRectItem *)cursor)->rect().height();
                    int repWidth = width/WldPlacingItems::itemW;
                    int repHeight = height/WldPlacingItems::itemH;

                    WorldData plSqScene;
                    for(int i = 0; i < repWidth; i++){
                        for(int j = 0; j < repHeight; j++){
                            WldPlacingItems::SceneSet.x = x + i * WldPlacingItems::itemW;
                            WldPlacingItems::SceneSet.y = y + j * WldPlacingItems::itemH;

                            WldData->scene_array_id++;

                            WldPlacingItems::SceneSet.array_id = WldData->scene_array_id;

                            WldData->scenery.push_back(WldPlacingItems::SceneSet);
                            placeScenery(WldPlacingItems::SceneSet, true);
                            plSqScene.scenery.push_back(WldPlacingItems::SceneSet);
                        }
                    }
                    if(plSqScene.scenery.size() > 0)
                    {
                        //addPlaceHistory(plSqScene);
                        //restart Animation
                    }
                }
            case PLC_Path:
                {
                    long x = cursor->scenePos().x();
                    long y = cursor->scenePos().y();
                    long width = ((QGraphicsRectItem *)cursor)->rect().width();
                    long height = ((QGraphicsRectItem *)cursor)->rect().height();
                    int repWidth = width/WldPlacingItems::itemW;
                    int repHeight = height/WldPlacingItems::itemH;

                    WorldData plSqPath;
                    for(int i = 0; i < repWidth; i++){
                        for(int j = 0; j < repHeight; j++){
                            WldPlacingItems::PathSet.x = x + i * WldPlacingItems::itemW;
                            WldPlacingItems::PathSet.y = y + j * WldPlacingItems::itemH;

                            WldData->path_array_id++;

                            WldPlacingItems::PathSet.array_id = WldData->path_array_id;

                            WldData->paths.push_back(WldPlacingItems::PathSet);
                            placePath(WldPlacingItems::PathSet, true);
                            plSqPath.paths.push_back(WldPlacingItems::PathSet);
                        }
                    }
                    if(plSqPath.paths.size() > 0)
                    {
                        //addPlaceHistory(plSqPath);
                        //restart Animation
                    }
                }
            case PLC_Level:
                {
                    long x = cursor->scenePos().x();
                    long y = cursor->scenePos().y();
                    long width = ((QGraphicsRectItem *)cursor)->rect().width();
                    long height = ((QGraphicsRectItem *)cursor)->rect().height();
                    int repWidth = width/WldPlacingItems::itemW;
                    int repHeight = height/WldPlacingItems::itemH;

                    WorldData plSqLevel;
                    for(int i = 0; i < repWidth; i++){
                        for(int j = 0; j < repHeight; j++){
                            WldPlacingItems::LevelSet.x = x + i * WldPlacingItems::itemW;
                            WldPlacingItems::LevelSet.y = y + j * WldPlacingItems::itemH;

                            WldData->level_array_id++;

                            WldPlacingItems::LevelSet.array_id = WldData->level_array_id;

                            WldData->levels.push_back(WldPlacingItems::LevelSet);
                            placeLevel(WldPlacingItems::LevelSet, true);
                            plSqLevel.levels.push_back(WldPlacingItems::LevelSet);
                        }
                    }
                    if(plSqLevel.levels.size() > 0)
                    {
                        //addPlaceHistory(plSqLevel);
                        //restart Animation
                    }
                }
            default:
                break;
            }
        cursor->hide();
        }
        break;
        }
    case MODE_PlacingNew:
        {
    //        if(placingItem == PLC_Door)
    //        {
    //            MainWinConnect::pMainWin->on_actionSelect_triggered();
    //            QGraphicsScene::mouseReleaseEvent(mouseEvent);
    //            return;
    //        }
        }
    default:
        break;
    }


    if(DrawMode)
    {
        QGraphicsScene::mouseReleaseEvent(mouseEvent);
        return;
    }

            cursor->hide();

            haveSelected = false;

            QString ObjType;
            int collisionPassed = false;

            //History
            WorldData historyBuffer; bool deleted=false;
            WorldData historySourceBuffer;

            if(PasteFromBuffer)
            {
                paste( WldBuffer, mouseEvent->scenePos().toPoint() );
                PasteFromBuffer = false;
                IsMoved=false;
                MainWinConnect::pMainWin->on_actionSelect_triggered();
            }


            QList<QGraphicsItem*> deleteList;
            deleteList.clear();
            QList<QGraphicsItem*> selectedList = selectedItems();

            // check for grid snap
            if ((!selectedList.isEmpty())&&(IsMoved))
            {

                // correct selected items' coordinates
                for (QList<QGraphicsItem*>::iterator it = selectedList.begin(); it != selectedList.end(); it++)
                { ////////////////////////FIRST FETCH///////////////////////
                    if(EditingMode==MODE_Erasing)
                    {

                        if(!(*it)->isVisible()) continue; //Invisible items can't be deleted

                        //remove data from main array before deletion item from scene
                        if( (*it)->data(0).toString()=="TILE" )
                        {
                            historyBuffer.tiles.push_back(((ItemTile *)(*it))->tileData);
                            ((ItemTile *)(*it))->removeFromArray();
                            deleted=true;
                        }
                        else
                        if( (*it)->data(0).toString()=="SCENERY" )
                        {
                            historyBuffer.scenery.push_back(((ItemScene *)(*it))->sceneData);
                            ((ItemScene *)(*it))->removeFromArray();
                            deleted=true;
                        }
                        else
                        if( (*it)->data(0).toString()=="PATH" )
                        {
                            historyBuffer.paths.push_back(((ItemPath *)(*it))->pathData);
                            ((ItemPath *)(*it))->removeFromArray();
                            deleted=true;
                        }
                        else
                        if( (*it)->data(0).toString()=="LEVEL" )
                        {
                            historyBuffer.levels.push_back(((ItemLevel *)(*it))->levelData);
                            ((ItemLevel *)(*it))->removeFromArray();
                            deleted=true;
                        }
                        removeItem((*it));
                        deleteList.push_back((*it));
                        continue;
                    }

                    /////////////////////////GET DATA///////////////

                    setItemSourceData((*it), (*it)->data(0).toString()); //Set Grid Size/Offset, sourcePosition

                    /////////////////////////GET DATA/////////////////////

                    //Check position
                    if( (WsourcePos == QPoint((long)((*it)->scenePos().x()), ((long)(*it)->scenePos().y()))))
                    {
                        ///SKIP NON-MOVED ITEMS
                        IsMoved=false;
                        #ifdef _DEBUG_
                        WriteToLog(QtDebugMsg, QString(" >>Collision skiped, posSource=posCurrent"));
                        #endif
                        continue;
                    }

                    ////////////////////Apply to GRID/////////////////////////////////
                    (*it)->setPos( QPointF(
                                       applyGrid( (*it)->scenePos().toPoint(),
                                                      WgridSize,
                                                      QPoint(WoffsetX, WoffsetY)
                                                  )
                                           )
                                  );
                    //////////////////////////////////////////////////////////////////

                } ////////////////////////FIRST FETCH///////////////////////

                if(!deleteList.isEmpty())
                {
                    while(!deleteList.isEmpty())
                    {
                        QGraphicsItem* tmp = deleteList.first();
                        deleteList.pop_front();
                        if(tmp!=NULL) delete tmp;
                    }
                }
                selectedList = selectedItems();

                if((EditingMode==MODE_Erasing)&&(deleted))
                {
                    //addRemoveHistory(historyBuffer);
                }
                EraserEnabled = false;

                // Check collisions
                //Only if collision ckecking enabled
                if(!PasteFromBuffer)
                for (QList<QGraphicsItem*>::iterator it = selectedList.begin(); it != selectedList.end(); it++)
                { ////////////////////////SECOND FETCH///////////////////////
                    ObjType = (*it)->data(0).toString();

                    #ifdef _DEBUG_
                    WriteToLog(QtDebugMsg, QString(" >>Check collision with \"%1\"").arg(ObjType));
                    #endif

                    setItemSourceData((*it), ObjType); //Set Grid Size/Offset, sourcePosition

                    //Check position
                    if( (WsourcePos == QPoint((long)((*it)->scenePos().x()), ((long)(*it)->scenePos().y()))))
                    {
                        ///SKIP NON-MOVED ITEMS
                        IsMoved=false;
                        #ifdef _DEBUG_
                        WriteToLog(QtDebugMsg, QString(" >>Collision skiped, posSource=posCurrent"));
                        #endif
                        continue;
                    }

                    if(opts.collisionsEnabled)
                    { //check Available to collisions checking
                        if( itemCollidesWith((*it)) )
                        {
                            collisionPassed = false;
                            (*it)->setPos(QPointF(WsourcePos));
                            (*it)->setSelected(false);
                            /*
                            WriteToLog(QtDebugMsg, QString("Moved back %1 %2")
                                       .arg((long)(*it)->scenePos().x())
                                       .arg((long)(*it)->scenePos().y()) );*/
                        }
                        else
                        {
                            collisionPassed = true;
                        }
                    }

                    if((collisionPassed) || (!opts.collisionsEnabled))
                    {
                        if( ObjType == "TILE")
                        {
                            //Applay move into main array
                            historySourceBuffer.tiles.push_back(((ItemTile *)(*it))->tileData);
                            ((ItemTile *)(*it))->tileData.x = (long)(*it)->scenePos().x();
                            ((ItemTile *)(*it))->tileData.y = (long)(*it)->scenePos().y();
                            ((ItemTile *)(*it))->arrayApply();
                            historyBuffer.tiles.push_back(((ItemTile *)(*it))->tileData);
                            WldData->modified = true;
                        }
                        else
                        if( ObjType == "SCENERY")
                        {
                            //Applay move into main array
                            historySourceBuffer.scenery.push_back(((ItemScene *)(*it))->sceneData);
                            ((ItemScene *)(*it))->sceneData.x = (long)(*it)->scenePos().x();
                            ((ItemScene *)(*it))->sceneData.y = (long)(*it)->scenePos().y();
                            ((ItemScene *)(*it))->arrayApply();
                            historyBuffer.scenery.push_back(((ItemScene *)(*it))->sceneData);
                            WldData->modified = true;
                        }
                        else
                        if( ObjType == "PATH")
                        {
                            //Applay move into main array
                            historySourceBuffer.paths.push_back(((ItemPath*)(*it))->pathData);
                            ((ItemPath *)(*it))->pathData.x = (long)(*it)->scenePos().x();
                            ((ItemPath *)(*it))->pathData.y = (long)(*it)->scenePos().y();
                            ((ItemPath *)(*it))->arrayApply();
                            historyBuffer.paths.push_back(((ItemPath *)(*it))->pathData);
                            WldData->modified = true;
                        }
                        else
                        if( ObjType == "LEVEL")
                        {
                            //Applay move into main array
                            historySourceBuffer.levels.push_back(((ItemLevel *)(*it))->levelData);
                            ((ItemLevel *)(*it))->levelData.x = (long)(*it)->scenePos().x();
                            ((ItemLevel *)(*it))->levelData.y = (long)(*it)->scenePos().y();
                            ((ItemLevel *)(*it))->arrayApply();
                            historyBuffer.levels.push_back(((ItemLevel *)(*it))->levelData);
                            WldData->modified = true;
                        }
                        else
                        if( ObjType == "MUSICBOX")
                        {
                            //Applay move into main array
//                            historySourceBuffer.bgo.push_back(((ItemBGO *)(*it))->bgoData);
//                            ((ItemBGO *)(*it))->bgoData.x = (long)(*it)->scenePos().x();
//                            ((ItemBGO *)(*it))->bgoData.y = (long)(*it)->scenePos().y();
//                            ((ItemBGO *)(*it))->arrayApply();
//                            historyBuffer.bgo.push_back(((ItemBGO *)(*it))->bgoData);
//                            WldData->modified = true;
                        }

                    }
                }////////////////////////SECOND FETCH///////////////////////

                //if((EditingMode==MODE_Selecting)&&(IsMoved)) addMoveHistory(historySourceBuffer, historyBuffer);

                IsMoved = false;

                QGraphicsScene::mouseReleaseEvent(mouseEvent);
                return;
           }
     EraserEnabled = false;
     QGraphicsScene::mouseReleaseEvent(mouseEvent);
}


void WldScene::setItemSourceData(QGraphicsItem * it, QString ObjType)
{
    WgridSize = pConfigs->default_grid;
    WoffsetX = 0;
    WoffsetY = 0;

    if( ObjType == "TILE")
    {
        WsourcePos = QPoint(  ((ItemTile *)it)->tileData.x, ((ItemTile *)it)->tileData.y);
        WgridSize = ((ItemTile *)it)->gridSize;
        WoffsetX = 0;
        WoffsetY = 0;
    }
    else
    if( ObjType == "SCENERY")
    {
        WsourcePos = QPoint(  ((ItemScene *)it)->sceneData.x, ((ItemScene *)it)->sceneData.y);
        WgridSize = ((ItemScene *)it)->gridSize;
        WoffsetX = 0;
        WoffsetY = 0;
    }
    else
    if( ObjType == "PATH")
    {
        WsourcePos = QPoint(  ((ItemPath *)it)->pathData.x, ((ItemPath *)it)->pathData.y);
        WgridSize = ((ItemPath *)it)->gridSize;
        WoffsetX = 0;
        WoffsetY = 0;
    }
    else
    if( ObjType == "LEVEL")
    {
        WsourcePos = QPoint(  ((ItemLevel *)it)->levelData.x, ((ItemLevel*)it)->levelData.y);
        WgridSize = ((ItemLevel *)it)->gridSize;
        WoffsetX = 0;
        WoffsetY = 0;
    }
    else
    if( ObjType == "MUSICBOX")
    {
//        sourcePos = QPoint(  ((ItemLevel *)it)->levelData.x, ((ItemLevel*)it)->levelData.y);
//        gridSize = ((ItemLevel *)it)->gridSize;
//        offsetX = 0;
//        offsetY = 0;
    }
}


void WldScene::placeItemUnderCursor()
{
    WorldData newData;
    bool wasPlaced=false;
    if( itemCollidesWith(cursor) )
    {
        return;
    }
    else
    {
        if(placingItem == PLC_Tile)
        {
            WldPlacingItems::TileSet.x = cursor->scenePos().x();
            WldPlacingItems::TileSet.y = cursor->scenePos().y();

            WldData->tile_array_id++;
            WldPlacingItems::TileSet.array_id = WldData->tile_array_id;

            WldData->tiles.push_back(WldPlacingItems::TileSet);
            placeTile(WldPlacingItems::TileSet, true);
            newData.tiles.push_back(WldPlacingItems::TileSet);
            wasPlaced=true;
        }
        else
        if(placingItem == PLC_Scene)
        {
            WldPlacingItems::SceneSet.x = cursor->scenePos().x();
            WldPlacingItems::SceneSet.y = cursor->scenePos().y();

            WldData->scene_array_id++;
            WldPlacingItems::SceneSet.array_id = WldData->scene_array_id;

            WldData->scenery.push_back(WldPlacingItems::SceneSet);
            placeScenery(WldPlacingItems::SceneSet, true);
            newData.scenery.push_back(WldPlacingItems::SceneSet);
            wasPlaced=true;
        }
        else
        if(placingItem == PLC_Path)
        {
            WldPlacingItems::PathSet.x = cursor->scenePos().x();
            WldPlacingItems::PathSet.y = cursor->scenePos().y();

            WldData->path_array_id++;
            WldPlacingItems::PathSet.array_id = WldData->path_array_id;

            WldData->paths.push_back(WldPlacingItems::PathSet);
            placePath(WldPlacingItems::PathSet, true);
            newData.paths.push_back(WldPlacingItems::PathSet);
            wasPlaced=true;
        }
        else
        if(placingItem == PLC_Level)
        {
            WldPlacingItems::LevelSet.x = cursor->scenePos().x();
            WldPlacingItems::LevelSet.y = cursor->scenePos().y();

            WldData->level_array_id++;
            WldPlacingItems::LevelSet.array_id = WldData->level_array_id;

            WldData->levels.push_back(WldPlacingItems::LevelSet);
            placeLevel(WldPlacingItems::LevelSet, true);
            newData.levels.push_back(WldPlacingItems::LevelSet);
            wasPlaced=true;
        }
        else
        if(placingItem == PLC_Musicbox)
        {
            WldPlacingItems::MusicSet.x = cursor->scenePos().x();
            WldPlacingItems::MusicSet.y = cursor->scenePos().y();

            WldData->musicbox_array_id++;
            WldPlacingItems::MusicSet.array_id = WldData->musicbox_array_id;

            WldData->music.push_back(WldPlacingItems::MusicSet);
            placeMusicbox(WldPlacingItems::MusicSet, true);
            newData.music.push_back(WldPlacingItems::MusicSet);
            wasPlaced=true;
        }

    }
    if(wasPlaced)
    {
        WldData->modified = true;
        //addPlaceHistory(newData);
    }

    //if(opts.animationEnabled) stopAnimation();
    //if(opts.animationEnabled) startBlockAnimation();
}


void WldScene::removeItemUnderCursor()
{
    if(contextMenuOpened) return;

    QGraphicsItem * findItem;
    bool removeIt=true;
    findItem = itemCollidesCursor(cursor);
    if(findItem)
    {
        if(findItem->data(0).toString()=="TILE")
        {
            if( (lock_tile)|| (((ItemTile *)findItem)->isLocked) )
            removeIt=false;
        }
        else
        if(findItem->data(0).toString()=="SCENERY")
        {
            if( (lock_scene) || (((ItemScene *)findItem)->isLocked) )
            removeIt=false;
        }
        else
        if(findItem->data(0).toString()=="PATH")
        {
            if( (lock_path) || (((ItemNPC *)findItem)->isLocked) )
            removeIt=false;
        }
        else
        if(findItem->data(0).toString()=="LEVEL")
        {
            if( (lock_level) || (((ItemLevel *)findItem)->isLocked) )
            removeIt=false;
        }
        else
        if(findItem->data(0).toString()=="MUSICBOX")
        {
            //if( (lock_musbox) || (((ItemXXX *)findItem)->isLocked) )
            removeIt=false;
        }

        if(!findItem->isVisible()) //Invisible items can't be deleted
            removeIt=false;

        if(removeIt)
        {
            WorldData removedItems;
            bool deleted=false;
            //remove data from main array before deletion item from scene
            if( findItem->data(0).toString()=="TILE" )
            {
                removedItems.tiles.push_back(((ItemTile *)findItem)->tileData);
                ((ItemTile *)findItem)->removeFromArray();
                deleted=true;
            }
            else
            if( findItem->data(0).toString()=="SCENERY" )
            {
                removedItems.scenery.push_back(((ItemScene *)findItem)->sceneData);
                ((ItemScene *)findItem)->removeFromArray();
                deleted=true;
            }
            else
            if( findItem->data(0).toString()=="PATH" )
            {
                removedItems.paths.push_back(((ItemPath *)findItem)->pathData);
                ((ItemPath *)findItem)->removeFromArray();
                deleted=true;
            }
            else
            if( findItem->data(0).toString()=="LEVEL" )
            {
                removedItems.levels.push_back(((ItemLevel *)findItem)->levelData);
                ((ItemLevel *)findItem)->removeFromArray();
                deleted=true;
            }
            else
            if( findItem->data(0).toString()=="MUSICBOX" )
            {
//                removedItems.bgo.push_back(((ItemBGO *)findItem)->bgoData);
//                ((ItemBGO *)findItem)->removeFromArray();
                deleted=true;
            }

              removeItem(findItem);
            delete findItem;
            if(deleted) removedItems.paths.size();//addRemoveHistory(removedItems);
        }
    }
}


void WldScene::SwitchEditingMode(int EdtMode)
{
    //int EditingMode; // 0 - selecting,  1 - erasing, 2 - placeNewObject
                     // 3 - drawing water/sand zone, 4 - placing from Buffer
    //bool EraserEnabled;
    //bool PasteFromBuffer;

    //bool DrawMode; //Placing/drawing on map, disable selecting and dragging items

    //bool disableMoveItems;

    //bool contextMenuOpened;
    EraserEnabled=false;
    PasteFromBuffer=false;
    DrawMode=false;
    disableMoveItems=false;

    switch(EdtMode)
    {
    case MODE_PlacingNew:
        DrawMode=true;
        //setSectionResizer(false, false);

        break;
    case MODE_DrawSquare:
        resetCursor();
        //setSectionResizer(false, false);
        DrawMode=true;
        break;

    case MODE_Resizing:
        resetCursor();
        DrawMode=true;
        disableMoveItems=true;
        break;

    case MODE_PasteFromClip:
        resetCursor();
        //setSectionResizer(false, false);
        disableMoveItems=true;
        break;

    case MODE_Erasing:
        resetCursor();
        //setSectionResizer(false, false);
        break;

    case MODE_SelectingOnly:
        resetCursor();
        //setSectionResizer(false, false);
        disableMoveItems=true;
        break;
    case MODE_Selecting:
    default:
        resetCursor();
        //setSectionResizer(false, false);
        break;
    }
    EditingMode = EdtMode;

}
