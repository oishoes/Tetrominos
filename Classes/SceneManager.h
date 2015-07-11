//
//  SceneManager.h
//  Tetrominos
//
//  Created by Shota Oiyama on 2015/07/01.
//
//

#ifndef __Tetrominos__SceneManager__
#define __Tetrominos__SceneManager__

#include <cocos2d.h>
#include "NetworkingWrapper.h"

class GameScene;
class SceneManager : public NetworkingDelegate {
public:
    static SceneManager* getInstance();
    
    void enterGameScene(bool networked);
    void returnToLobby();
    void showPeerList();
    void receiveMultiplayerInvitations();
    void sendData(const void* data, unsigned long length);
    
private:
    std::unique_ptr<NetworkingWrapper> netWorkingWrapper;
    GameScene* gameScene;
    
    SceneManager();
    ~SceneManager();
    
    void receivedData(const void* data, unsigned long length);
    void stateChanged(ConnectionState state);
};
#endif /* defined(__Tetrominos__SceneManager__) */
