using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace RuntimeDumper
{
    public interface IModule<T>
    {
        void PushToStack(T key, object value);
        bool IsOnStack(T key);
        object GrabFromStack(T key);

        bool HasNext();
        T Next();
    }
}
