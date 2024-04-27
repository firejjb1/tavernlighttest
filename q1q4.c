Q1-Q4 - Fix or improve the implementation of the below methods.

Q1 - Fix or improve the implementation of the below methods

local function releaseStorage(player)
    player:setStorageValue(1000, -1)
end

function onLogout(player)
    -- NOTE: if condition removed
    -- NOTE: addEvent has the information of 1000 being the key, so it should call getStorageValue instead.
    addEvent(releaseStorage, 1000, player)
    return true
end


Q2 - Fix or improve the implementation of the below method

function printSmallGuildNames(memberCount)
    -- this method is supposed to print names of all guilds that have less than memberCount max members
    local selectGuildQuery = "SELECT name FROM guilds WHERE max_members < %d;"
    -- NOTE: is storeQuery is correct method?
    local resultId = db.storeQuery(string.format(selectGuildQuery, memberCount))
    -- NOTE: result is undefined, resultId is unused. not sure how to fix this without knowing how db is implemented
    local guildName = result.getString("name")
    print(guildName)
end


Q3 - Fix or improve the name and the implementation of the below method

function do_sth_with_PlayerParty(playerId, membername)
    player = Player(playerId)
    local party = player:getParty()
    -- no need to loop to find member if there is a function to remove a player from the party already
    party:removeMember(Player(membername))

    --for k,v in pairs(party:getMembers()) do
    --    if v == Player(membername) then
    --        party:removeMember(Player(membername))
    --    end
    --end
end

Q4 - Assume all method calls work fine. Fix the memory leak issue in below method

void Game::addItemToPlayer(const std::string& recipient, uint16_t itemId)
{
    Player* player = g_game.getPlayerByName(recipient);
    // NOTE: move item logic earlier so that player memory leak doesn't depend on item related logic
    Item* item = Item::CreateItem(itemId);
    if (!item) {
        return;
    }
    if (!player) {
        player = new Player(nullptr);
        if (!IOLoginData::loadPlayerByName(player, recipient)) {
            // NOTE: delete player if return to prevent memory leak
            delete player;
            return;
        }
    }
    g_game.internalAddItem(player->getInbox(), item, INDEX_WHEREEVER, FLAG_NOLIMIT);

    if (player->isOffline()) {
        IOLoginData::savePlayer(player);
    }
}
