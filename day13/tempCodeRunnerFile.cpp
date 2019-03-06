 if (g.get(curr.x+1, curr.y) == 0 && !g.getFlag(curr.x+1, curr.y))
            deq.emplace_front(Pos(curr.x+1,curr.y,curr.val+1));
        
        if (g.get(curr.x, curr.y+1) == 0 && !g.getFlag(curr.x, curr.y+1))
            deq.emplace_front(Pos(curr.x,curr.y+1,curr.val+1));