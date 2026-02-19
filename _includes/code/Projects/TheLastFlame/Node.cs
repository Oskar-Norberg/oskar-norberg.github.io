namespace Ringo.AI
{
    public abstract class Node
    {
        protected BlackBoard.BlackBoard BlackBoard;
        
        public enum ReturnValue
        {
            Success,
            Failure
        }

        public abstract ReturnValue Evaluate();

        public virtual void PopulateBlackBoard(BlackBoard.BlackBoard blackBoard)
        {
            BlackBoard = blackBoard;
        }
    }
}