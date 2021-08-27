// Copyright (C) 2019-2020 Zilliz. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance
// with the License. You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software distributed under the License
// is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
// or implied. See the License for the specific language governing permissions and limitations under the License.

package datanode

import (
	"context"

	"go.uber.org/zap"

	"github.com/milvus-io/milvus/internal/log"
)

type deleteNode struct {
	BaseNode

	replica Replica
}

func (ddn *deleteNode) Name() string {
	return "deletedNode"
}

func (ddn *deleteNode) Operate(in []Msg) []Msg {
	// log.Debug("DDNode Operating")

	if len(in) != 1 {
		log.Error("Invalid operate message input in deleteNode", zap.Int("input length", len(in)))
		return []Msg{}
	}

	if len(in) == 0 {
		return []Msg{}
	}

	msMsg, ok := in[0].(*MsgStreamMsg)
	if !ok {
		log.Error("type assertion failed for MsgStreamMsg")
		return []Msg{}
		// TODO: add error handling
	}

	if msMsg == nil {
		return []Msg{}
	}

	return []Msg{}
}

func newDeleteDNode(ctx context.Context, replica Replica) *deleteNode {
	baseNode := BaseNode{}
	baseNode.SetMaxParallelism(Params.FlowGraphMaxQueueLength)

	return &deleteNode{
		BaseNode: baseNode,
		replica:  replica,
	}
}