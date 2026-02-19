using System.Collections.Generic;

namespace Ringo.AI.BlackBoard
{
    public class BlackBoard
    {
        private Dictionary<string, object> data = new Dictionary<string, object>();

        public bool TryGetData(string key, out object value)
        {
            return data.TryGetValue(key, out value);
        }

        public void SetData(string key, object value)
        {
            data[key] = value;
        }
    }
}