 
Proto4z.register(10000,"DictGlobal") 
Proto4z.DictGlobal = {} --全局配置 
Proto4z.DictGlobal.__protoID = 10000 
Proto4z.DictGlobal.__protoName = "DictGlobal" 
Proto4z.DictGlobal[1] = {name="id", type="ui32" }  
Proto4z.DictGlobal[2] = {name="val", type="ui64" }  
Proto4z.DictGlobal[3] = {name="combo", type="string" }  
Proto4z.DictGlobal[4] = {name="desc", type="string" }  
 
Proto4z.register(10001,"DictRafflePool") 
Proto4z.DictRafflePool = {} --道具抽奖,道具掉落 
Proto4z.DictRafflePool.__protoID = 10001 
Proto4z.DictRafflePool.__protoName = "DictRafflePool" 
Proto4z.DictRafflePool[1] = {name="id", type="ui32" }  
Proto4z.DictRafflePool[2] = {name="raffleType", type="ui16" } --0 独立随机, 有多少个道具配置随机多少次, 1根据总体权重随机一个 
Proto4z.DictRafflePool[3] = {name="raffleCount", type="i32" } --批量抽取次数 
Proto4z.DictRafflePool[4] = {name="pool", type="string" } --格式为kv数据, 其中v为浮点 [道具ID:概率或权重, 道具ID:概率或权重] 
 
Proto4z.register(10002,"DictFightEffect") 
Proto4z.DictFightEffect = {} --战斗属性效果,用于装备,属性类增减益buff 
Proto4z.DictFightEffect.__protoID = 10002 
Proto4z.DictFightEffect.__protoName = "DictFightEffect" 
Proto4z.DictFightEffect[1] = {name="id", type="ui32" }  
Proto4z.DictFightEffect[2] = {name="hp", type="double" } --血量值 
Proto4z.DictFightEffect[3] = {name="hpRegen", type="double" } --每秒血量值恢复 
Proto4z.DictFightEffect[4] = {name="attack", type="double" } --伤害 
Proto4z.DictFightEffect[5] = {name="defense", type="double" } --防御 
Proto4z.DictFightEffect[6] = {name="crit", type="double" } --暴击 
Proto4z.DictFightEffect[7] = {name="toughness", type="double" } --韧性 
Proto4z.DictFightEffect[8] = {name="moveSpeed", type="double" } --移动速度 
Proto4z.DictFightEffect[9] = {name="attackSpeed", type="double" } --攻击速度 
Proto4z.DictFightEffect[10] = {name="vampirk", type="double" } --吸血 
 
Proto4z.register(10003,"DictItem") 
Proto4z.DictItem = {} --道具字典 
Proto4z.DictItem.__protoID = 10003 
Proto4z.DictItem.__protoName = "DictItem" 
Proto4z.DictItem[1] = {name="id", type="ui32" }  
Proto4z.DictItem[2] = {name="primitiveType", type="ui16" } --主类型 
Proto4z.DictItem[3] = {name="subType", type="ui16" } --子类型 
Proto4z.DictItem[4] = {name="visible", type="ui16" } --是否可见 
Proto4z.DictItem[5] = {name="stacks", type="ui16" } --可堆叠个数,0和1都是1次 
Proto4z.DictItem[6] = {name="fightEffectID", type="ui32" } --战斗属性效果,装备后生效 
Proto4z.DictItem[7] = {name="autoUse", type="ui16" } --0 不可使用, 1 可使用, 2 获得后自动使用 
Proto4z.DictItem[8] = {name="dropID", type="ui32" } --DictRafflePool中的id, 使用后销毁本道具并根据配置进行道具抽取 
Proto4z.DictItem[9] = {name="vocationLimit", type="ui16" } --限制职业类型, 装备类型 
Proto4z.DictItem[10] = {name="levelLimit", type="i32" } --限制职业最小等级, 装备类型 
Proto4z.DictItem[11] = {name="desc", type="string" }  