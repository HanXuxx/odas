
    /**
    * \file     con_categories.c
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-03-18
    * \copyright
    *
    * This program is free software: you can redistribute it and/or modify
    * it under the terms of the GNU General Public License as published by
    * the Free Software Foundation, either version 3 of the License, or
    * (at your option) any later version.
    *
    * This program is distributed in the hope that it will be useful,
    * but WITHOUT ANY WARRANTY; without even the implied warranty of
    * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    * GNU General Public License for more details.
    * 
    * You should have received a copy of the GNU General Public License
    * along with this program.  If not, see <http://www.gnu.org/licenses/>.
    *
    */
    
    #include <connector/con_categories.h>

    con_categories_obj * con_categories_construct(const unsigned int nOuts, const msg_categories_cfg * msg_categories_config) {

        con_categories_obj * obj;
        unsigned int iOut;

        obj = (con_categories_obj *) malloc(sizeof(con_categories_obj));

        obj->nOuts = nOuts;

        obj->in = msg_categories_construct(msg_categories_config);

        obj->outs = (msg_categories_obj **) malloc(sizeof(msg_categories_obj *) * nOuts);
        for (iOut = 0; iOut < obj->nOuts; iOut++) {
            obj->outs[iOut] = msg_categories_construct(msg_categories_config);
        }

        return obj;

    }

    void con_categories_destroy(con_categories_obj * obj) {

        unsigned int iOut;

        for (iOut = 0; iOut < obj->nOuts; iOut++) {
            msg_categories_destroy(obj->outs[iOut]);
        }
        free((void *) obj->outs);

        msg_categories_destroy(obj->in);

        free((void *) obj);

    }

    int con_categories_process(con_categories_obj * obj) {

        unsigned int iOut;
        int rtnValue;

        for (iOut = 0; iOut < obj->nOuts; iOut++) {
            msg_categories_copy(obj->outs[iOut], obj->in);
        }

        if (msg_categories_isZero(obj->in) == 1) {
            rtnValue = -1;
        }
        else {
            rtnValue = 0;
        }

        return rtnValue;

    }
