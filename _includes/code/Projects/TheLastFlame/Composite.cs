using System.Collections.Generic;

namespace Ringo.AI
{
    public abstract class Composite : Node
    {
        protected List<Node> Children;

        protected Composite(List<Node> children)
        {
            Children = children;
        }

        public abstract override ReturnValue Evaluate();
    
        public override void PopulateBlackBoard(BlackBoard.BlackBoard blackBoard)
        {
            base.PopulateBlackBoard(blackBoard);
        
            foreach (Node child in Children)
            {
                child.PopulateBlackBoard(BlackBoard);
            }
        }
    }
}