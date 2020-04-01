using Agony;
using Agony.SDK.Enumerations;
using Agony.SDK.Pathing;
using Agony.SDK.TreeSharp;
using Agony.SDK.Utils;
using SharpDX;
using System;
using System.Xml;
using Action = Agony.SDK.TreeSharp.Action;

namespace Gathering.Decorators
{
    public static class FindNode
    {
        static bool ShouldTakeAction()
        {
            if
            (
                Gathering.NodeObject == null ||
                Gathering.NodeObject.Type == Agony.WoWObjectType.Invalid
            )
            {
                Gathering.NodeObject = null;
                return true;
            }
            return false;
        }

        static Action TakeAction()
        {
            return new Action(a =>
            {
                try
                {
                    Logger.Log(LogLevel.Info, "[Gathering] Searching node.");
                    Gathering.NodeObject = null;
                    //Look for any NODE arround...

                    //If no nodes arround, move to a hotspot...
                    if (Gathering.NodeObject == null)
                    {
                        XmlNode hotspots = Gathering.Profile["HBProfile"]["Hotspots"];
                        if (Gathering.HotspotIndex == -1 || Gathering.HotspotIndex == hotspots.ChildNodes.Count)
                        {
                            Gathering.HotspotIndex = 0;
                        }
                        var currentHotspot = hotspots.ChildNodes.Item(Gathering.HotspotIndex);
                        var x = float.Parse(currentHotspot.Attributes.GetNamedItem("X").Value);
                        var y = float.Parse(currentHotspot.Attributes.GetNamedItem("Y").Value);
                        var z = float.Parse(currentHotspot.Attributes.GetNamedItem("Z").Value);
                        var hotspotPosition = new Vector3(x, y, z);
                        var distance = Vector3.Distance(hotspotPosition, Game.Me.Position);
                        Logger.Log(LogLevel.Debug, string.Format("Distance: {0}, Pos: ({1}, {2}, {3}), Target: ({4}, {5}, {6}) | {7}", distance, Game.Me.Position.X, Game.Me.Position.Y, Game.Me.Position.Z, hotspotPosition.X, hotspotPosition.Y, hotspotPosition.Z, Game.Me.Name));
                        if (distance < 3)
                        {
                            Gathering.HotspotIndex++;
                        }
                        else
                        {
                            MoveTo.Move(hotspotPosition);
                        }
                    }
                }
                catch(Exception ex)
                {
                    Logger.Log(LogLevel.Error, ex.Message + Environment.NewLine + ex.StackTrace);
                }
            });
        }

        public static Composite BehaviorComposite => new Decorator(t => ShouldTakeAction(), TakeAction());
    }
}