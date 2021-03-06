/*
 * ForwardChainer.h
 *
 * Copyright (C) 2014,2015 Misgana Bayetta
 *
 * Author: Misgana Bayetta <misgana.bayetta@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License v3 as
 * published by the Free Software Foundation and including the exceptions
 * at http://opencog.org/wiki/Licenses
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program; if not, write to:
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef FORWARDCHAINERX_H_
#define FORWARDCHAINERX_H_

#include <opencog/util/Logger.h>
#include <opencog/rule-engine/JsonicControlPolicyParamLoader.h>
#include <opencog/rule-engine/URECommons.h>
#include "FCMemory.h"

class ForwardChainerUTest;

namespace opencog
{

class ForwardChainerCallBack;
class ForwardChainer {
private:
    friend class ::ForwardChainerUTest;

    AtomSpace * _as;
    URECommons _rec; //utility class

    JsonicControlPolicyParamLoader* _cpolicy_loader;

	string _conf_path;

    FCMemory _fcmem; //Stores history
    Logger * _log;
    int _iteration = 0;

    /**
     * initialize config methods
     */
    void init();
    void add_to_source_list(Handle h);

    void do_pm();
    void do_pm(const Handle& hsource, const UnorderedHandleSet& var_nodes,
               ForwardChainerCallBack& fcb);
protected:
    enum source_selection_mode {
        TV_FITNESS_BASED, STI_BASED
    };
public:
    ForwardChainer(AtomSpace * as, const string& conf_path);
    virtual ~ForwardChainer();
    void step(ForwardChainerCallBack& fcb);
    void do_chain(ForwardChainerCallBack& fcb, Handle hsource =
            Handle::UNDEFINED);
    HandleSeq get_chaining_result(void);

    void setLogger(Logger* log);
    Logger* getLogger(void);
};

} // ~namespace opencog

#endif /* FORWARDCHAINERX_H_ */
