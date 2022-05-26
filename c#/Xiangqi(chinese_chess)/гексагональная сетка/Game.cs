using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace гексагональная_сетка
{
    public class Game
    {
        public Map map;
        public GameState gs = GameState.None;
        public List<Player> Winners = new List<Player>();
        public List<Player> players = new List<Player>();
        public bool WasNearMove = false;
        public Player currentPlayer;
        public Game()
        {
            
            map = new Map();
        }

        public void StartGame(int colv)
        {
            // TODO Очистка списка с игроками. prizeNo = 0;
            gs = GameState.SelectFishka;
            SetPlayers(colv);
            
            WasNearMove = false;
        }
        public void SetPlayers(int colv)
        {
            int d = 3 - colv;
            for (int i = 1; i <= 6; i += d)
            {
                players.Add(new Player() { cellType = (Type)i });
            }
            currentPlayer = players[0];
            PrepairMap();
        }
        public void PrepairMap()
        {

            List<Cell> cs = new List<Cell>();
            map.cells.ForEach(c => cs.AddRange(c));
            
            //var list = cs.Where(
            //    c => players.Select(p=>p.cellType).ToList().Contains(c.needType)
            //    );
            foreach (var item in cs.Where(c=>c.currentType!= Type.none && c.currentType != Type.empty))
            {
                if (!players.Select(p => p.cellType).ToList().Contains(item.currentType))
                {
                    item.currentType = Type.empty;
                }
               
            }
                    
            //foreach (var cell in cs)
            //{

            //    if (players.Find(x=> x.cellType == cell.currentType) == null)
            //    {
            //        cell.currentType = Type.none;
            //    }
            //    if ()
            //    {
            //        cell.needType = Type.none;
            //    }
            //}

        }

        public void NextPlayer()
        {
            if (ChecWin(currentPlayer))
            {
                if (!Winners.Contains(currentPlayer))
                {
                    Winners.Add(currentPlayer);
                }
            }
            if (Winners.Count == players.Count)
            {
                gs = GameState.GameOver;
                return;
            }


            for (int i = 0; i < players.Count; i++)
            {
               
                int ind = players.IndexOf(currentPlayer);
                int nextInd = ind == players.Count - 1 ? 0 : ind + 1;
                currentPlayer = players[nextInd];
                if (!Winners.Contains(currentPlayer))
                {
                    break;
                }
            }

            map.selectedCell = null;
            gs = GameState.SelectFishka;
            WasNearMove = false;
        }

        public void Draw(Graphics gr)
        {
           map.Draw(gr);
        }


        public bool ChecWin(Player pl)
        {
            bool res = false;
            List<Cell> cs = new List<Cell>();
            map.cells.ForEach(c => cs.AddRange(c));

            int count = cs.Count(x => (x.currentType == x.needType) && (x.currentType == pl.cellType));
            if (count == 1)
            {
                res = true;
            }
            return res;
        }
        public void Select(PointF p)
        {
            Cell cell = map.GetCell(p);
            if (gs == GameState.SelectFishka)
            {
                
                if (cell != null)
                {
                    if (cell.currentType == currentPlayer.cellType)
                    {
                        map.SetSelectedCell(cell);
                        gs = GameState.SelectMove;
                    }
                   
                }  
            }
            else if (gs == GameState.SelectMove)
            {
                if (map.moveCells.Contains(cell))
                {
                    
                    Type currentType = cell.currentType;
                    cell.currentType = map.selectedCell.currentType;
                    map.selectedCell.currentType = currentType;
                    WasNearMove = true;
                    if (cell.sosedi.Any(sosed => sosed.Near == map.selectedCell)  || !WasNearMove)
                    {

                        NextPlayer();
                        
                    }
                    else
                    {
                        map.SetSelectedCell(cell,!WasNearMove);
                        
                    }

                    // Выбор следующего хода этого же игрока
                    //gs = GameState.SelectFishka; // Для отладки

                    //map.SetSelectedCell(null);
                    //
                }      
            }
        }
    }
}
